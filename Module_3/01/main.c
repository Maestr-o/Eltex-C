#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Введите длины сторон!\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid;
    switch (pid = fork()) {
        case -1: {
            printf("Ошибка создания процесса!\n");
            exit(EXIT_FAILURE);
        }
        case 0: {
            for (int i = 1; i < argc; i += 2) {
                calc(atof(argv[i]));
            }
            exit(EXIT_SUCCESS);
        }
        default: {
            for (int i = 2; i < argc; i += 2) {
                calc(atof(argv[i]));
            }
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}