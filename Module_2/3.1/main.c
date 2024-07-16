#include "header.h"

#include <stdio.h>

void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int c;
    printf("----------------------------------------\n");
    printf("Выберите действие:\n1. Ввести права доступа в буквенном обозначении\n2. Ввести права доступа в цифровом обозначении\n3. Выбрать файл\n");
    printf("----------------------------------------\n");
    scanf("%d", &c);
    int bin = 0;
    switch (c) {
        case 1: {
            input_letter_permissions(&bin);
            break;
        }
        case 2: {
            input_digit_permissions(&bin);
            break;
        }
        case 3: {
            int num = input_file(&bin);
            if (num != -1) {
                printf("Числовое: %d\n", num);
                output_letters(bin_to_oct(bin));
            } else {
                printf("Ошибка!\n");
                return;
            }
            break;
        }
        default: {
            printf("Выбран неверный пункт!\n");
            return;
        }
    }
    output_bits(bin);
}