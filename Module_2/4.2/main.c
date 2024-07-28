#include "header.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    PriorityQueue queue;
    init(&queue);
    while (1) {
        printf("--------------------\n");
        printf("Выберите действие:\n1. Добавить элемент\n2. Извлечь первый в очереди элемент\n3. Извлечь элемент с заданным приоритетом\n4. Извлечь элемент с приоритетом не ниже заданного\n0. Выход\n");
        printf("-------Дерево-------\n");
        if (is_empty(&queue)) printf("       Пусто!\n");
        else print(&queue, 0, 0);
        printf("--------------------\n");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 0: {
                exit(EXIT_SUCCESS);
            }
            case 1: {
                int priority;
                char data[MSG_MAX_SIZE];
                system("clear");
                printf("Введите приоритет: ");
                scanf("%d", &priority);
                printf("Введите сообщение: ");
                input_string(data);
                system("clear");
                add(&queue, priority, data);
                break;
            }
            case 2: {
                system("clear");
                extract_first(&queue);
                break;
            }
            case 3: {
                system("clear");
                printf("Введите приоритет: ");
                int priority;
                scanf("%d", &priority);
                system("clear");
                extract_priority(&queue, priority);
                break;
            }
            case 4: {
                system("clear");
                printf("Введите приоритет: ");
                int priority;
                scanf("%d", &priority);
                system("clear");
                extract_priority_more(&queue, priority);
                break;
            }
            default: {
                system("clear");
                printf("Неверный пункт!\n");
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}