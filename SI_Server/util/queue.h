typedef struct Node {
    char* data;
    struct Node *next;
} Node;

typedef struct Queue {
    int size;
    struct Node *first;
    struct Node *last;
} Queue;
