typedef struct Node {
    char* data;
    struct Node *next;
} Node;

typedef struct Queue {
    int size;
    struct Node *first;
    struct Node *last;
} Queue;

Queue* queue_create();
void queue_push(Queue* q, char* value);
char* queue_pop(Queue* q);
int queue_empty(Queue* q);
int queue_size(Queue* q);
