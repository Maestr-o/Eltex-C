#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Введите числа!\n");
        exit(EXIT_FAILURE);
    }
    double res = atof(argv[1]);
    for (int i = 2; i < argc; i++) {
        double x = atof(argv[i]);
        if (x > res) res = x;
    }
    printf("Ответ: %lf\n", res);
    return EXIT_SUCCESS;
}