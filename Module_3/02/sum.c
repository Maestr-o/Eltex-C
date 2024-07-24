#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Введите числа!\n");
        exit(EXIT_FAILURE);
    }
    double res = 0.0;
    for (int i = 1; i < argc; i++) {
        double x = atof(argv[i]);
        res += x;
    }
    printf("Ответ: %lf\n", res);
    return EXIT_SUCCESS;
}