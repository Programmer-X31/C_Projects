#include "snake.h"
#include <stddef.h>

/* enqueue - add a node at the end of the queue. allows for two queues to be added */
Node *enqueue(Snake *s, Node *n) {
    if(s == NULL) {
        if((s = createsnake()) != NULL)
            return NULL;
        return s;
    }

    if(s->head == NULL)
        s->head = n;

    if(s->tail == NULL) {
        s->tail = n;
    }

    s->tail->next = n;
    s->tail = n;

    return s;
}

Point dequeue(Snake *s) {
    if(s->head == NULL)
        return {-1, -1};
    
    Point tmp;
    tmp = s->head->pt;
    s->head = s->head->next;
    return tmp;
}

Snake *createsnake() {
    return (Snake *) malloc(sizeof(Snake));
}
void move(Snake *);
void draw(Snake *);
void grow(Snake *);
