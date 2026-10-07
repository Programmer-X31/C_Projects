#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "dirent.h"
#include <sys/stat.h>
#include <sys/types.h>

void fsize(char *);

int main(int argc, char *argv[]) {
	if(argc == 1)
		fsize(".");
	else
		while(--argc > 0)
			fsize(*++argv);
	return 0;
}
