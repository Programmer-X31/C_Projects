#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define NAME '1'

int getop(char []);
void push(double);
double pop();
void clear();
void mathfnc(char s[]);

int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case NAME:
                mathfnc(s);
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
                    printf("error: zero divisor\n");
                break;
            case 't':
                op2 = pop();
                printf("\t%.8g\n", op2);
                push(op2);
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}


#define MAXVAL 100

int sp = 0;
double val[MAXVAL]; // The list of numbers maintaining the stack

void push(double f)
{
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if(sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void clear()
{
    sp = 0;    
}

int getch(void);
void ungetch(int);

// /* getop - gets the next operator or numeric operand */
// int getop(char s[])
// {
//     int i, c, sign;
//     sign = 1;

//     while((s[0] = c = getch()) ==  ' ' || c == '\t')
//         ;
    
//     s[1] = '\0';

//     if(!isdigit(c) && c != '.')
//         return c;

//     i = 0;

//     if(isdigit(c))
//         while(isdigit(s[++i] = c = getch()))
//             ;

//     if(c == '.')
//         while(isdigit(s[++i] = c = getch()))
//             ;
//     s[i] = '\0';

//     if(c != EOF)
//         ungetch(c);
//     return NUMBER;
// }

int getop(char s[])
{
    int i, c, sign;
    sign = 1;

    while((s[0] = c = getch()) ==  ' ' || c == '\t')
        ;
    
    s[1] = '\0';

    i = 0;
    if(islower(c)) {
        while(islower(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if(c != EOF)
            ungetch(c);
        if(strlen(s) > 1)
            return NAME;
        else
            return c;
    }


    if(!isdigit(c) && c != '.')
        while(isdigit(s[++i] = c = getch()))
            ;
    if(isdigit(c))
        while(isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

void mathfnc(char *s)
{
    if(strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if(strcmp(s, "cos") == 0)
        push(cos(pop()));
    else if(strcmp(s, "tan") == 0)
        push(tan(pop()));
    else
        printf("error: unknown command %s\n", s);
}



#define BUFSIZE 100

char buf[BUFSIZE]; // The buffer size aka the max size of an operand
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if(bufp > BUFSIZE)
        printf("ungetch: too many characters");
    else
        buf[bufp++] = c;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
          int (*comp)(void *, void *))
{
   int i, last;
   void swap(void *v[], int, int);
   if (left >= right)    /* do  nothing if array contains */
       return;           /* fewer than two elements */
   swap(v, left, (left + right)/2);
   last = left;
   for (i = left+1; i <= right;  i++)
       if ((*comp)(v[i], v[left]) < 0)
           swap(v, ++last, i);
   swap(v, left, last);
   qsort(v, left, last-1, comp);
   qsort(v, last+1, right, comp);
}
