#include "header.h"

#include <stdio.h>
#include <stdarg.h>

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

double sub(int n, ...) { //
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

double call_sum(int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return sum(n, array[0]);
        case 2:
            return sum(n, array[0], array[1]);
        case 3:
            return sum(n, array[0], array[1], array[2]);
        case 4:
            return sum(n, array[0], array[1], array[2], array[3]);
        case 5:
            return sum(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return sum(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}

double call_sub(int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return sub(n, array[0]);
        case 2:
            return sub(n, array[0], array[1]);
        case 3:
            return sub(n, array[0], array[1], array[2]);
        case 4:
            return sub(n, array[0], array[1], array[2], array[3]);
        case 5:
            return sub(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return sub(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}

double call_mult(int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return mult(n, array[0]);
        case 2:
            return mult(n, array[0], array[1]);
        case 3:
            return mult(n, array[0], array[1], array[2]);
        case 4:
            return mult(n, array[0], array[1], array[2], array[3]);
        case 5:
            return mult(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return mult(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}

double call_div(int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return divide(n, array[0]);
        case 2:
            return divide(n, array[0], array[1]);
        case 3:
            return divide(n, array[0], array[1], array[2]);
        case 4:
            return divide(n, array[0], array[1], array[2], array[3]);
        case 5:
            return divide(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return divide(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}

double call_max(int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return max(n, array[0]);
        case 2:
            return max(n, array[0], array[1]);
        case 3:
            return max(n, array[0], array[1], array[2]);
        case 4:
            return max(n, array[0], array[1], array[2], array[3]);
        case 5:
            return max(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return max(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}

double call_min(int n, double array[MAX_NUMBERS]) {
    switch (n) {
        case 1:
            return min(n, array[0]);
        case 2:
            return min(n, array[0], array[1]);
        case 3:
            return min(n, array[0], array[1], array[2]);
        case 4:
            return min(n, array[0], array[1], array[2], array[3]);
        case 5:
            return min(n, array[0], array[1], array[2], array[3], array[4]);
        default:
            return min(n, array[0], array[1], array[2], array[3], array[4], array[5]);
    }
}