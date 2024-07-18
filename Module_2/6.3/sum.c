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