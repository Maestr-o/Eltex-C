#include <stdarg.h>

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