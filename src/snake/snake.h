typedef struct {
    int x;
    int y;
} Point;

typedef struct node {
    Point pt;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    unsigned int length;
} Snake;


Snake *createsnake();
void move(Snake *);
void draw(Snake *);
void grow(Snake *);


