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
        printf("----------------------------------------\n");
        printf("Выберите действие:\n1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление\n5. Максимум\n6. Минимум\n");
        printf("----------------------------------------\n");
        int c, n;
        scanf("%d", &c);
        printf("Введите кол-во чисел (от 2 до %d): ", MAX_NUMBERS);
        scanf("%d", &n);
        if (n >= 2 && n <= MAX_NUMBERS) {
            double array[MAX_NUMBERS];
            for (int i = 0; i < n; i++) {
                printf("%d-е число: ", i + 1);
                scanf("%lf", &array[i]);
            }
            switch (c) {
                case 1: {
                    printf("Ответ: %lf\n", call_sum(n, array));
                    break;
                }
                case 2: {
                    printf("Ответ: %lf\n", call_sub(n, array));
                    break;
                }
                case 3: {
                    printf("Ответ: %lf\n", call_mult(n, array));
                    break;
                }
                case 4: {
                    printf("Ответ: %lf\n", call_div(n, array));
                    break;
                }
                case 5: {
                    printf("Ответ: %lf\n", call_max(n, array));
                    break;
                }
                case 6: {
                    printf("Ответ: %lf\n", call_min(n, array));
                    break;
                }
                default: {
                    printf("Введено неверное значение!\n");
                    break;
                }
            }
        } else {
            system("clear");
            printf("Кол-во чисел от 2 до %d!\n", MAX_NUMBERS);
        }
    }
}