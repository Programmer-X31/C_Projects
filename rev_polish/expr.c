#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define BUFSIZE 100

int getop(char []);
char ungets(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;
double val[MAXVAL]; /* stack */
char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */


int main(int argc, char *argv[])
{
	char s[MAXOP];
	double op2;

	while(--argc > 0)
	{
		ungets(" ");
		ungets(*++argv);
		switch(getop(s))
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					fprintf(stderr, "zero error occurred\n");
				break;
			default:
				fprintf(stderr, "error: unknown command%s\n", s);
				argc = 1;
				break;
		}
		printf("\t%.8g\n", pop());
		return 0;
	}
}

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f); /*  Error Handling  */
}

/* pop: pop and return the top value from the stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error : stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if ((!isdigit(c) || c == 's') && c != '.')
		return c;

	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
/* getch: get a pushed back character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

char ungets(char s[])
{
	int len = strlen(s);
	void ungetch(int);


	while(len > 0)
		ungetch(s[--len]);
}

/* ungetch: push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch:  too many characters");
	else
		buf[bufp++] = c;
}
