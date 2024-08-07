#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int create_sem() {
    key_t sem_key = ftok(SEM_FILE, KEY_SEM);
    int sem_id = semget(sem_key, 1, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        printf("Ошибка создания семафора\n");
        exit(EXIT_FAILURE);
    }
    union semun sem_union;
    sem_union.val = 0;
    semctl(sem_id, 0, SETVAL, sem_union);
    return sem_id;
}

void sem_p(int sem_id) { // сброс состояния
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -2;
    sem_op.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_op, 1);
}

void sem_v(int sem_id) { // следующий шаг
    int sem_val = semctl(sem_id, 0, GETVAL);
    if (sem_val >= SEM_MAX) return;
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_op, 1);
}

int init_shm() {
    int shm_fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1 || ftruncate(shm_fd, sizeof(SharedData)) == -1) {
        perror("Ошибка создания разделяемой памяти");
        exit(EXIT_FAILURE);
    }
    SharedData* data = mmap(0, sizeof(SharedData), PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("Ошибка подключения разделяемой памяти");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }
    data->count = 0;
    data->done = 0;
    return shm_fd;
}

void child_process(int sem_id, int shm_fd) {
    int sval = semctl(sem_id, 0, GETVAL);
    switch (sval) {
        case -1:
            exit(EXIT_SUCCESS);
        case 1: {
            SharedData* data = mmap(0, sizeof(SharedData), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
            if (data == MAP_FAILED) {
                perror("Ошибка подключения разделяемой памяти");
                close(shm_fd);
                exit(EXIT_FAILURE);
            }
            int max = data->arr[0], min = data->arr[0];
            for (int i = 1; i < data->count; i++) {
                if (data->arr[i] < min) {
                    min = data->arr[i];
                } else if (data->arr[i] > max) {
                    max = data->arr[i];
                }
            }
            data->min = min;
            data->max = max;
            sem_v(sem_id);
            break;
        }
        default:
            break;
    }
}

void parent_process(int sem_id, int shm_fd) {
    int sval = semctl(sem_id, 0, GETVAL);
    switch (sval) {
        case -1:
            exit(EXIT_SUCCESS);
        case 0: {
            srand(time(NULL));
            int n = rand() % 10 + 1;
            int shm_size = sizeof(int) * n;
            int* set = (int*)malloc(shm_size);
            for (int i = 0; i < n; i++) {
                set[i] = rand() % 100;
            }

            SharedData* data = mmap(0, sizeof(SharedData), PROT_WRITE, MAP_SHARED, shm_fd, 0);
            if (data == MAP_FAILED) {
                perror("Ошибка подключения разделяемой памяти");
                close(shm_fd);
                exit(EXIT_FAILURE);
            }
            data->count = n;
            for (int i = 0; i < n; i++) {
                data->arr[i] = set[i];
            }
            free(set);
            sem_v(sem_id);
            break;
        }
        case 2: {
            SharedData* data = mmap(0, sizeof(SharedData), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
            if (data == MAP_FAILED) {
                perror("Ошибка подключения разделяемой памяти");
                close(shm_fd);
                exit(EXIT_FAILURE);
            }
            printf("Min: %d, max: %d\n", data->min, data->max);
            data->done++;
            sem_p(sem_id);
            break;
        }
        default:
            break;
    }
}

void quit_parent() {
    int shm_fd = shm_open(SHM_FILE, O_RDONLY, 0666);
    SharedData* data = mmap(0, sizeof(SharedData), PROT_READ, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("Ошибка подключения разделяемой памяти");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }
    printf("\nКол-во обработанных наборов: %d\n", data->done);
    close(shm_fd);
    munmap(data, sizeof(SharedData));
    shm_unlink(SHM_FILE);
    printf("Завершение родительского процесса...\n");
}

void quit_child() {
    key_t sem_key = ftok(SEM_FILE, KEY_SEM);
    int sem_id = semget(sem_key, 1, 0666);
    semctl(sem_id, 0, IPC_RMID);
    printf("Завершение дочернего процесса...\n");
}