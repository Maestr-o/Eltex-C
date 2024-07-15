#include "header.h"

#include <stdio.h>
#include <stdlib.h>

void menu();

Operation ops[N_OPS] = {
    {"Сумма", sum},
    {"Разность", sub},
    {"Деление", divide},
    {"Умножение", mult},
    {"Максимум", max},
    {"Минимум", min}
};

int main() {
    menu();
    return 0;
}

void menu() {
    while (1) {
        printf("----------------------------------------\n");
        printf("Выберите действие:\n");
        print_operations(ops);
        printf("----------------------------------------\n");
        int c, n;
        scanf("%d", &c);
        if (c < 1 || c > N_OPS) {
            system("clear");
            printf("Введено неверное значение!\n");
            continue;
        }
        printf("Введите кол-во чисел (от 2 до %d): ", MAX_NUMBERS);
        scanf("%d", &n);
        if (n >= 2 && n <= MAX_NUMBERS) {
            double array[MAX_NUMBERS];
            for (int i = 0; i < n; i++) {
                printf("%d-е число: ", i + 1);
                scanf("%lf", &array[i]);
            }
            printf("Ответ: %lf\n", call_action(ops[c - 1].func, n, array));
        } else {
            system("clear");
            printf("Кол-во чисел от 2 до %d!\n", MAX_NUMBERS);
        }
    }
}