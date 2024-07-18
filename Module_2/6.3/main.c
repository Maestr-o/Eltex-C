#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dlfcn.h>

#define MAX_NUMBERS 5
#define MAX_SYMBOLS 30
#define N_OPS 6

typedef double (*operation)(int n, ...);

typedef struct {
	char name[MAX_SYMBOLS];
	operation func;
} Operation;

void print_operations(Operation ops[N_OPS]);
double call_action(double (*operation)(int, ...), int n, double array[MAX_NUMBERS]);
void check_lib(void* lib);

int main() {
    double (*sum)(int, ...);
    double (*sub)(int, ...);
    double (*mult)(int, ...);
    double (*divide)(int, ...);
    double (*max)(int, ...);
    double (*min)(int, ...);

    void* libsum = dlopen("./libsum.so", RTLD_LAZY);
    check_lib(libsum);
    sum = dlsym(libsum, "sum");

    void* libsub = dlopen("./libsub.so", RTLD_LAZY);
    check_lib(libsub);
    sub = dlsym(libsub, "sub");

    void* libmult = dlopen("./libmult.so", RTLD_LAZY);
    check_lib(libmult);
    mult = dlsym(libmult, "mult");

    void* libdivide = dlopen("./libdivide.so", RTLD_LAZY);
    check_lib(libdivide);
    divide = dlsym(libdivide, "divide");

    void* libmax = dlopen("./libmax.so", RTLD_LAZY);
    check_lib(libmax);
    max = dlsym(libmax, "max");

    void* libmin = dlopen("./libmin.so", RTLD_LAZY);
    check_lib(libmin);
    min = dlsym(libmin, "min");

    Operation ops[N_OPS] = {
        {"Сумма", sum},
        {"Разность", sub},
        {"Деление", divide},
        {"Умножение", mult},
        {"Максимум", max},
        {"Минимум", min}
    };

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

    dlclose(libsum);
    dlclose(libsub);
    dlclose(libmult);
    dlclose(libdivide);
    dlclose(libmax);
    dlclose(libmin);
    return 0;
}

void print_operations(Operation ops[N_OPS]) {
    for (int i = 0; i < N_OPS; i++) {
        printf("%d. %s\n", i + 1, ops[i].name);
    }
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

void check_lib(void* lib) {
    if (!lib) {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
}