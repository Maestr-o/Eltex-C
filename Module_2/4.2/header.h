#ifndef HEADER_H
#define HEADER_H

#define MSG_MAX_SIZE 256
#define QUEUE_MAX_SIZE 200
#define MAX_PRIORITY 255

typedef struct {
    int priority;
    char data[MSG_MAX_SIZE];
} Item;

typedef struct {
    Item items[QUEUE_MAX_SIZE];
    int size;
} PriorityQueue;

void add(PriorityQueue* queue, int priority, char data[MSG_MAX_SIZE]);
void extract_first(PriorityQueue* queue);
void extract_priority(PriorityQueue* queue, int priority);
void extract_priority_more(PriorityQueue* queue, int priority);

void init(PriorityQueue* queue);
int is_empty(PriorityQueue* queue);
int is_full(PriorityQueue* queue);
void push(PriorityQueue* queue, Item item);
Item pop(PriorityQueue* queue, int i);
void swap(Item* item1, Item* item2);
void up(PriorityQueue* queue, int i);
void down(PriorityQueue* queue, int i);
void print(PriorityQueue* pq, int index, int indent);
void input_string(char str[MSG_MAX_SIZE]);

#endif