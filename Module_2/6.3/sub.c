#include <stdarg.h>

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