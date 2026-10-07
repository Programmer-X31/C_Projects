#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>

typedef struct node {
    Vector2 vec;
    struct node *prev;
    struct node *next;
} Node;

typedef enum {TOP, LEFT, BOTTOM, RIGHT} Direction;

typedef struct {
    Node *head;
    Node *tail;
    unsigned int length;
    unsigned int dir: 2;
} Snake;

Snake *createSnake();
void moveSnake(Snake *);
void drawSnake(Snake *);
void growSnake(Snake *);

int addHead(Snake *s, Vector2 vec);
Vector2 removeTail(Snake *s);

#endif