/*
 * =====================================================================================
 *
 *       Filename:  syscalls.
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  11/27/2022 08:31:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Programmer-X31 (),
 *   Organization:
 *
 * =====================================================================================
 */

#include "syscall.h"
#include <fcntl.h>

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* Max no. of files open at once */

typedef struct _iobuf {
	int cnt;    /* characters left */
	char *ptr;  /* next character location */
	char *base; /* location of buffer */
	int flag;   /* mode of file access */
	int fd;	    /* file descriptors */
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020,
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}
