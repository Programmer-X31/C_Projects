#define NAME_MAX 14       /* longest filename */

typedef struct {          /* Directory Entry */
	long ino;					/* inode number */
	char name[NAME_MAX+1];		/* name + '\0' */
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} DIR;

DIR *opendir(char *dirname); /* to open a directory */
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);


