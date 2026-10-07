/**********************************************
* Program: rev_polish/term.c
* Description: Should evaluate a rev polish list of arguments
*
* Author: David
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

void push(double n);
double pop();

int main(int argc, char *argv[]) {
    // Since we will be given a list of operands, no need for maipulating buffers
    char *end;
    double n;
    double val, op2;

    while(--argc > 0) {
        n = strtod(*++argv, &end);
        if(strcmp(end, "") == 0) {
            // Actually a double. Push to stack
            push(n);
            continue;
        }
        switch(*end) {
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
                printf("error: unknown command\n");
                break;

        }
        /*
        if(strcmp(end, "+") == 0)
            push(pop() + pop());
        else if(strcmp(end, "*") == 0)
            push(pop() * pop());
        else if(strcmp(end, "-") == 0) {
            op2 = pop();
            push(pop() - op2);
        } else if(strcmp(end, "/") == 0) {
            op2 = pop();
            if(op2 == 0.0) {
                printf("error: division by 0\n");
                return -1;
            }
            push(pop() / op2);
        }
            */

    }

    printf("%lf\n", pop());

}

static double stack[MAXLEN];
static double *p = stack;

void push(double n)
{
    if(p - stack > MAXLEN-1) {
        printf("error: stack is full\n");
        return;
    }
    *p++ = n; 
}

double pop() {
    if(p != stack)
        return *--p;
    printf("error: stack empty\n");
    return 0.0;
}

