#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 1000
char buf[BUFSIZE];
char *bufp = buf;

/* getch - function to read the buffer if its not empty and getting input from user if it is */
int getch(void) { return (bufp != buf) ? *bufp-- : getchar(); }

/* ungetch - pushing a character into the buffer */
void ungetch(int c) {
	if ((bufp - buf) > BUFSIZE)
		printf("ungetch: buffer size exceeds %d", BUFSIZE);
	else
		*bufp++ = c;
}

/* flush - clear buffer */
void flush() { bufp = buf; }

int getint(int *pn)
{
    int c, sign;

    while(isspace(c = getch()))
        ;
    if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); // Not a number
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if(c == '+' || c == '-')
        c = getch();
    for(*pn = 0; isdigit(c); c = getch())
        *pn = (10 * *pn) + (c - '0');
    *pn *= sign;

    if(c != EOF)
        ungetch(c);
    return c;
}


void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for(p = fmt; *p; p++) {
        if(*p != '%') { // Not a flag
            putchar(*p);
            continue;
        }
        switch(*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;

            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}

/*
 * @brief Minimal Scanf function - Gets int, double and string input using flags
 * @param fmt format string
 * @param ... arguments to put into format
 * */
int minscanf(char *fmt, ...)
{
    va_list ap;
    char c;                   /* current character     */
    char *p;                  /* moving across pointer */
    int count = 0;            /* count of valid params */
    int *ip;                  /* Int input             */
    double *dp;               /* Double input          */
    char *sp;                 /* String Input          */

    va_start(ap, fmt);
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            // Non flag stuff
            continue;
        }
        switch(*++p) {
            case 'd':
                ip = va_arg(ap, int*);
                // while(isspace(c = getch()))
                //     ;
                // if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
                //     ungetch(c);
                //     break;
                // }
                // int sign = (c == '-') ? -1 : 1;
                // while(isdigit(c = getch())) {
                //     *ip = (10 * *ip) + (c - '0');
                // }
                // ungetch(c); // Remove the last '\n' signifying the end of the input
                // count++;
                // *ip *= sign;
                if(getint(ip) != 0)
                    count++;
                break;
            case 's':
                sp = va_arg(ap, char*);
                while(isalnum(c = getch())) {
                    *sp++ = c;
                }
                ungetch(c); // Enter newline
                count++;
                break;

        }
    }
    va_end(ap);
    return count;
}

int main() {
    int x, y;
    char s[50];
    minscanf("%d", &x);
    flush();
    minscanf("%s", s);
    printf("%d - %s\n", x, s);
}
