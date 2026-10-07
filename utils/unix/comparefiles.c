#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;

	char *prog = argv[0];

	void filecomp(FILE *fp1, FILE *fp2);

	if(argc != 3) {
		fprintf(stderr, "%s: incorrect number of arguments\n", prog);
		exit(1);
	} else {
		if((fp1 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
			exit(1);
		} else if((fp2 = fopen(*++argv, "r")) == NULL) {
			fprintf(stderr, "%s: cant open %s\n", prog, *argv);
			exit(1);
		} else {
			filecomp(fp1, fp2);
			fclose(fp1);
			fclose(fp2);

			exit(0);
		}
	}
}

void filecomp(FILE *fp1, FILE *fp2)
{
	char line1[MAXLINE], line2[MAXLINE];
	char *lp1, *lp2;

	int lineno;

	lineno = 1;

	do {
		// Getting Lines
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);

		if(lp1 == line1 && lp2 == line2) {
			if(strcmp(line1, line2) != 0) {
				printf("first difference in line\n%d |\t%s\n``", lineno, line1);
				lp1 = lp2 = NULL;
			}
		} else if(lp1 != line1 && lp2 == line2) {
			printf("end of first file at line\n%s\n", line2);
		}
		else if(lp1 == line1 && lp2 != line2) {
			printf("end of second file at line\n%s\n", line1);
		}
		++lineno;
	} while(lp1 == line1 && lp2 == line2);
}

