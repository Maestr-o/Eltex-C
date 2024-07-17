#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    Item* head = NULL;
    while (1) {
        printf("----------------------------------------\n");
        printf("Выберите действие:\n1. Просмотреть список контактов\n2. Добавить новый контакт\n3. Удалить контакт\n4. Редактировать контакт\n0. Выход\n");
        printf("----------------------------------------\n");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 0:
                return;
            case 1:
                print_list(head);
                break;
            case 2: {
                system("clear");
                head = add_contact(head);
                break;
            }
            case 3: {
                system("clear");
                printf("Введите номер контакта: ");
                int n;
                scanf("%d", &n);
                head = del_contact(head, n - 1);
                break;
            }
            case 4: {
                system("clear");
                printf("Введите номер контакта: ");
                int n;
                scanf("%d", &n);
                head = edit_contact(head, n - 1);
                break;
            }
            default: {
                system("clear");
                printf("Введено неверное значение!\n");
                break;
            }
        }
    }
}