/*
 * =====================================================================================
 *
 *       Filename:  cat.c
 *
 *    Description: A C implementation of the cat command on UNIX operating
 * systems.
 *
 *        Version:  1.0
 *        Created:  11/27/2022 01:01:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Programmer-X31 (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	void filecopy(FILE *, FILE *);

	char *progname = argv[0];

	if (argc == 1) {
		filecopy(stdin, stdout);
	} else {
		while (--argc > 0) {
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s", progname,
					*argv);
				exit(1);
			} else {
				filecopy(fp, stdout);
				fclose(fp);
			}
		}
	}

	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", progname);
		exit(2);
	}
	exit(0);
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	while ((c = getc(ifp)) != EOF) {
		putc(c, ofp);
	}
}
