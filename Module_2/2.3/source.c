#include "header.h"

#include <stdio.h>
#include <stdarg.h>

void print_operations(Operation ops[N_OPS]) {
    for (int i = 0; i < N_OPS; i++) {
        printf("%d. %s\n", i + 1, ops[i].name);
    }
}

double sum(int n, ...) {
    double res = 0.0;
    va_list factor;
    va_start(factor, n);
    for (int i = 0; i < n; i++) {
        res += va_arg(factor, double);
    }
    va_end(factor);
    return res;
}

double sub(int n, ...) {
    va_list factor;
    va_start(factor, n);
    double res = va_arg(factor, double);
    for (int i = 1; i < n; i++) {
        res -= va_arg(factor, double);
    }
    va_end(factor);
    return res;
}

double mult(int n, ...) {
    va_list factor;
    va_start(factor, n);
    double res = va_arg(factor, double);
    for (int i = 1; i < n; i++) {
        res *= va_arg(factor, double);
    }
    va_end(factor);
    return res;
}

double divide(int n, ...) {
    va_list factor;
    va_start(factor, n);
    double res = va_arg(factor, double);
    for (int i = 1; i < n; i++) {
        res /= va_arg(factor, double);
    }
    va_end(factor);
    return res;
}

double max(int n, ...) {
    va_list factor;
    va_start(factor, n);
    double res = va_arg(factor, double);
    for (int i = 1; i < n; i++) {
        double num = va_arg(factor, double);
        if (num > res) {
            res = num;
        }
    }
    va_end(factor);
    return res;
}

double min(int n, ...) {
    va_list factor;
    va_start(factor, n);
    double res = va_arg(factor, double);
    for (int i = 1; i < n; i++) {
        double num = va_arg(factor, double);
        if (num < res) {
            res = num;
        }
    }
    va_end(factor);
    return res;
}

double call_action(double (*operation)(int, ...), int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return operation(n, array[0]);
        case 2:
            return operation(n, array[0], array[1]);
        case 3:
            return operation(n, array[0], array[1], array[2]);
        case 4:
            return operation(n, array[0], array[1], array[2], array[3]);
        case 5:
            return operation(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return operation(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}