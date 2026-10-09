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

Snake *snake_init();
void snake_move(Snake *);
void drawSnake(Snake *);
void growSnake(Snake *);

int snake_addHead(Snake *s, Vector2 vec);
Vector2 snake_removeTail(Snake *s);

#endif