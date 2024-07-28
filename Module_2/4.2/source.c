#include "header.h"

#include <stdio.h>
#include <string.h>

void init(PriorityQueue* queue) {
    queue->size = 0;
}

int is_empty(PriorityQueue* queue) {
    return queue->size == 0;
}

int is_full(PriorityQueue* queue) {
    return queue->size == QUEUE_MAX_SIZE;
}

void push(PriorityQueue* queue, Item item) {
    queue->items[queue->size] = item;
    queue->size++;
    up(queue, queue->size - 1);
}

Item pop(PriorityQueue* queue, int i) {
    Item extracted = queue->items[i];
    swap(&queue->items[queue->size - 1], &queue->items[i]);
    memset(queue->items[queue->size - 1].data, 0, MSG_MAX_SIZE);
    memset(&queue->items[queue->size - 1].priority, 0, sizeof(int));
    queue->size--;
    down(queue, i);
    return extracted;
}

void up(PriorityQueue* queue, int i) {
    while (i != 0 && queue->items[i].priority > queue->items[(i - 1) / 2].priority) {
        swap(&queue->items[i], &queue->items[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void down(PriorityQueue* queue, int i) {
    while (2 * i + 1 < queue->size) {
        int max_child_i = 2 * i + 1;
        if (queue->items[max_child_i + 1].priority > queue->items[max_child_i].priority) {
            max_child_i++;
        }
        if (queue->items[max_child_i].priority > queue->items[i].priority) {
            swap(&queue->items[max_child_i], &queue->items[i]);
            i = max_child_i;
        } else {
            break;
        }
    }
}

void swap(Item* item1, Item* item2) {
    Item tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}

void print(PriorityQueue* queue, int index, int indent) {
    if (index >= queue->size) return;
    for (int i = 0; i < indent; i++) printf("      ");
    printf("%s(%d)\n", queue->items[index].data, queue->items[index].priority);
    print(queue, index * 2 + 1, indent + 1);
    print(queue, index * 2 + 2, indent + 1);
}

void add(PriorityQueue* queue, int priority, char data[MSG_MAX_SIZE]) {
    if (is_full(queue)) {
        printf("Очередь переполнена!\n");
        return;
    }
    if (priority < 0 || priority > MAX_PRIORITY) {
        printf("Приоритет должен быть от 0 до %d!\n", MAX_PRIORITY);
        return;
    }
    Item item;
    item.priority = priority;
    memset(item.data, 0, MSG_MAX_SIZE); 
    strncpy(item.data, data, MSG_MAX_SIZE - 1);
    push(queue, item);
}

void extract_first(PriorityQueue* queue) {
    if (queue->size == 0) {
        printf("Нечего извлекать!\n");
        return;
    }
    Item extracted = pop(queue, 0);
    printf("Извлечен: %s(%d)\n", extracted.data, extracted.priority);
}

void extract_priority(PriorityQueue* queue, int priority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->items[i].priority == priority) {
            Item extracted = pop(queue, i);
            printf("Извлечен: %s(%d)\n", extracted.data, extracted.priority);
            return;
        }
    }
    printf("Элемент с приоритетом %d не найден!\n", priority);
}

void extract_priority_more(PriorityQueue* queue, int priority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->items[i].priority >= priority) {
            Item extracted = pop(queue, i);
            printf("Извлечен: %s(%d)\n", extracted.data, extracted.priority);
            return;
        }
    }
    printf("Элемент с приоритетом не ниже %d не найден!\n", priority);
}

void input_string(char str[MSG_MAX_SIZE]) {
    int ch;
    int length = 0;
    while (1) {
        length = 0;
        while ((ch = getchar()) != '\n' && ch != EOF && length < MSG_MAX_SIZE - 1) {
            str[length++] = ch;
        }
        str[length] = '\0';
        if (length == MSG_MAX_SIZE - 1) {
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        if (length > 0) {
            break;
        }
    }
}