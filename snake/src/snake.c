#include <stddef.h>
#include <stdlib.h>
#include "../include/snake.h"

/* Snake -> Queue
 * The Snake is a queue with Vector2 to the previous element
 * Thus, the head of the snake(part of the snake that moves is the end of the
 * queue(rear) The tail of the snake(the part that gets cut every frame) is the
 * start of the queue(front) Tail Vector2s to the previous element and it keep
 * going till it reaches the head
 */



Node *createNode(const Vector2 vec, const Node *prev, const Node *next) {
    Node* nn = (Node *) malloc(sizeof(Node));
    if(nn == NULL) return NULL;
    nn->vec = vec;
    nn->next = next;
    nn->prev = prev;

    return nn;
}

Vector2 *ptcpy(const Vector2 pt) {
    Vector2 *npt = (Vector2 *) malloc(sizeof(Vector2));
    npt->x = pt.x;
    npt->y = pt.y;
    return npt;
}

Vector2 snake_removeTail(Snake *s) {
	// Remove the node at the tail of a snake
	Node *tmp = s->tail;
	Vector2 p = s->tail->vec;
	s->tail = s->tail->prev;
	free(tmp);
	return p;
}

#define ERR_ADDHEAD 1

int snake_addHead(Snake *s, Vector2 vec)
{
	// Add a new node to the head of a snake
	Node *nn;

	if((nn = createNode(vec, NULL, s->head)) == NULL)
		return ERR_ADDHEAD;

	s->head->prev = nn;
	s->head = nn;

	return 0;
}

Snake *snake_init() {
	Snake *s = (Snake *)malloc(sizeof(Snake));
	// s->head = (Node) {(Vector2) {0, 0}, NULL, NULL};
	s->head = createNode((Vector2) {0, 0}, NULL, NULL);
    s->tail = s->head;
    s->dir = TOP;
    s->length = 1;
	return s;
}


void snake_move(Snake *s)
{
	// Remove an element from the tail of the snake(front of the queue)
    snake_removeTail(s);

	// Add a node to the head of the Snake(rear of the queue)
	Vector2 *headpt = ptcpy(s->head->vec);
	if (s->dir == TOP) {
		(headpt->y)++;
	} else if (s->dir == LEFT) {
		(headpt->x)--;
	} else if (s->dir == BOTTOM) {
		(headpt->y)--;
	} else if (s->dir == RIGHT) {
		(headpt->x)++;
	}
	snake_addHead(s, *headpt);
}

void snake_draw(Snake *)
{

}
void snake_update(Snake *s);

void snake_grow(Snake *s, Vector2 vec) {
	s->length++;
	snake_addHead(s, vec);

}
