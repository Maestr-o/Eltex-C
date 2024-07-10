#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    while (1) {
        printf("Выберите действие:\n1. Просмотреть список контактов\n2. Добавить новый контакт\n3. Удалить контакт\n4. Редактировать контакт\n0. Выход\n");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 0:
                return;
            case 1:
                if (!print_list()) {
                    system("clear");
                    printf("Список пуст!\n");
                }
                break;
            case 2:
                if (!add_contact()) {
                    system("clear");
                    printf("Ошибка добавления!\n");
                }
                break;
            case 3:
                if (!del_contact) {
                    system("clear");
                    printf("Ошибка удаления!\n");
                }
                break;
            case 4:
                if (!edit_contact()) {
                    system("clear");
                    printf("Ошибка редактирования!\n");
                }
                break;
            default:
                system("clear");
                printf("Введено неверное значение!\n");
                break;
        }
    }
}