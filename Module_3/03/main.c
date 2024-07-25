#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void menu();

int main() {
    menu();
    return EXIT_SUCCESS;
}

void menu() {
    Contact contacts[MAX_CONTACTS];
    read_db(contacts);
    while (1) {
        printf("----------------------------------------\n");
        printf("Выберите действие:\n1. Просмотреть список контактов\n2. Добавить новый контакт\n3. Удалить контакт\n4. Редактировать контакт\n0. Сохранить и выйти\n");
        printf("----------------------------------------\n");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 0: {
                write_db(contacts);
                exit(EXIT_SUCCESS);
            }
            case 1: {
                print_list(contacts);
                break;
            }
            case 2: {
                system("clear");
                if (add_contact(contacts) != 0) {
                    system("clear");
                    printf("Ошибка добавления!\n");
                }
                break;
            }
            case 3: {
                system("clear");
                if (del_contact(contacts) != 0) {
                    system("clear");
                    printf("Ошибка удаления!\n");
                }
                break;
            }
            case 4: {
                system("clear");
                if (edit_contact(contacts) != 0) {
                    system("clear");
                    printf("Ошибка редактирования!\n");
                }
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