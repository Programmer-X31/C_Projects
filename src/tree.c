#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

#undef strdup

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main(int argc, char *argv[]) {
	struct tnode *root;
	char word[MAXLEN];
	root = NULL;
	while (getword(word, MAXLEN) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *strdup2(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	if (p == NULL) {  /* a new word has arrived */
		p = talloc(); /* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;	   /* repeated word */
	else if (cond < 0) /* less than into left subtree */
		p->left = addtree(p->left, w);
	else /* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *talloc() { return (struct tnode *)malloc(sizeof(struct tnode)); }

char *strdup2(char *s) /* make a duplicate of s */
{
	char *p;
	p = (char *)malloc(strlen(s) + 1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
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

/* getword: get next word or character from input */
int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int comment(void) {
	int c;
	while ((c == getch()) != EOF)
		if (c == '*')
			if ((c = getch()) == '/') {
				break;
			} else {
				ungetch(c);
			}
}
