#include <stdio.h>

#define MAXLINE 1000 /* Max Limit */

int max;
char curr_line[MAXLINE];
char longest[MAXLINE];

int getline(char *line, int max);
void copy(void);

int main()
{
	int len;
	extern int max;
	extern char longest[];

	printf("Enter lines: \n");
	max = 0;
	while ((len = getline(curr_line, MAXLINE, stdin)) > 0)
		if (len > max)
		{
			max = len;
			copy();
		}
	if (max > 0)
		printf("Longest Line: %s", longest);
	return 0;
}

int getline(char *line, int max)
{
	if(fgets(line, max, stdin) == NULL)
		return NULL;
	else
		return strlen(line);
}

void copy(void)
{
	int i;
	extern char curr_line[], longest[];

	i = 0;
	while ((longest[i] = curr_line[i]) != '\0')
		++i;
}
