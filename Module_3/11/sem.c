#include "sem.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void sem_create() {
    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, SEM_MAX);
    if (sem == SEM_FAILED) {
        perror("Ошибка создания семафора\n");
        exit(EXIT_FAILURE);
    }
    sem_close(sem);
}

void sem_p() {
    while (1) {
        sem_t* sem = sem_open(SEM_NAME, 0);
        if (sem == SEM_FAILED) {
            perror("Ошибка открытия семафора для P-операции\n");
            sleep(1); continue;
        }
        if (sem_wait(sem) != 0) {
            printf("Ошибка выполнения P-операции\n");
            sem_close(sem);
            sleep(1); continue;
        }
        sem_close(sem);
        break;
    }
}

void sem_v() {
    while (1) {
        sem_t* sem = sem_open(SEM_NAME, 0);
        if (sem == SEM_FAILED) {
            perror("Ошибка открытия семафора для V-операции\n");
            sleep(1); continue;
        }
        if (sem_post(sem) != 0) {
            printf("Ошибка выполнения V-операции\n");
            sem_close(sem);
            sleep(1); continue;
        }
        int sval;
        if (sem_getvalue(sem, &sval) != 0 || sval > SEM_MAX) {
            sem_close(sem);
            printf("Выход за максимальное значение семафора\n");
            sleep(1); continue;
        }
        sem_close(sem);
        break;
    }
}

void sem_write() {
    while (1) {
        sem_t* sem = sem_open(SEM_NAME, 0);
        if (sem == SEM_FAILED) {
            perror("Ошибка открытия семафора для V-операции\n");
            sleep(1); continue;
        }
        int sval;
        if (sem_getvalue(sem, &sval) != 0) {
            printf("Ошибка получения значения семафора\n");
            sem_close(sem);
            sleep(1); continue;
        }
        if (sval >= SEM_MAX) {
            if (sem_wait(sem) != 0) {
                printf("Ошибка выполнения P-операции\n");
                sem_close(sem);
                sleep(1); continue;
            }
        } else {
            sem_close(sem);
            sleep(1); continue;
        }
        sem_close(sem);
        break;
    }
}