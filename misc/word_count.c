#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct key {
	char *word;
	int count;
} keytab[] = {
	{"auto", 0},   {"break", 0},	{"case", 0},	{"char", 0},
	{"const", 0},  {"continue", 0}, {"default", 0}, {"do", 0},
	{"double", 0}, {"else", 0},		{"enum", 0},	{"extern", 0},
	{"float", 0},  {"for", 0},		{"goto", 0},	{"if", 0},
	{"int", 0},	   {"include", 0},	{"long", 0},	{"register", 0},
	{"return", 0}, {"short", 0},	{"signed", 0},	{"sizeof", 0},
	{"static", 0}, {"struct", 0},	{"switch", 0},	{"typedef", 0},
	{"union", 0},  {"unsigned", 0}, {"void", 0},	{"volatile", 0},
	{"while", 0},
};

int getword(char *, int);
int binsearch(char *, struct key *, int);

#define MAXWORD 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

int main() {
	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++) {
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	}

	return 0;
}

int binsearch(char *word, struct key tab[], int n) {
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *s = word;
	int iscomment = 0;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*s++ = c;
	switch (c) {
	case EOF:
		break;
	case '/':
		if ((c = getch()) == '*')
			iscomment = 1;

	default:
		*s++ = c;
		break;
	}
	if (!isalpha(c)) {
		*s = '\0';
		return c;
	}

	for (; --lim > 0; s++) {
		if (!isalnum(*s = getch())) {
			ungetch(*s);
			break;
		}
		switch (*s) {
		case '*':
			if (!iscomment)
				break;
			if ((*s = getch()) != '/')
				iscomment = 0;
		default:
			*s = getch();
		}
	}

	while (--lim > 0) {
		switch (*s) {
		case '*':
			if (!iscomment)
				break;
			if ((*s++ = getch()) == '/')
				iscomment = 0;
		default:
			*s++ = getch();
		}
	}

	if (!iscomment) {
		*s = '\0';
		return word[0];
	}
	return -1;
}

#define BUFSIZE 1000
char buf[BUFSIZE];
char *bufp = buf;

/* Function to read the buffer if its not empty and getting input from user if
 * it is */
int getch(void) { return (bufp == buf) ? *bufp-- : getchar(); }

// Pushing a character into the buffer
void ungetch(int c) {
	if ((bufp - buf) > BUFSIZE)
		printf("ungetch: buffer size exceeds %d", BUFSIZE);
	else
		*bufp++ = c;
}
