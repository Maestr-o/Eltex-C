#include "sem.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void sem_create() {
    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, SEM_MAX);
    if (sem == SEM_FAILED) {
        perror("Ошибка создания семафора");
        exit(EXIT_FAILURE);
    }
    sem_close(sem);
}

void sem_p() {
    sem_t* sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        printf("Ошибка открытия семафора для P-операции\n");
        exit(EXIT_FAILURE);
    }
    if (sem_wait(sem) != 0) {
        printf("Ошибка выполнения P-операции\n");
        sem_close(sem);
        exit(EXIT_FAILURE);
    }
    sem_close(sem);
}

void sem_v() {
    sem_t* sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("Ошибка открытия семафора для V-операции");
        exit(EXIT_FAILURE);
    }
    int sval;
    if (sem_getvalue(sem, &sval) != 0 || sval >= SEM_MAX) {
        sem_close(sem);
        printf("Выход за максимальное значение семафора\n");
        exit(EXIT_FAILURE);
    }
    if (sem_post(sem) != 0) {
        perror("Ошибка выполнения V-операции");
        sem_close(sem);
        exit(EXIT_FAILURE);
    }
    sem_close(sem);
}