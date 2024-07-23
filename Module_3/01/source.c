#include "header.h"

#include <stdio.h>

double square(double a) {
    return a * a;
}

void calc(double a) {
    if (a <= 0) {
        printf("Длина не может быть нулевой или отрицательной (%lf)\n", a);
    } else {
        printf("Площадь квадрата со стороной %lf = %lf\n", a, square(a));
    }
}