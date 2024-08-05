#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

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

void init_shm() {
    key_t key_shm = ftok(SHM_FILE, KEY_SHM);
    int shm_id = shmget(key_shm, sizeof(SharedData), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        printf("Ошибка создания сегмента разделяемой памяти [parent]\n");
        exit(EXIT_FAILURE);
    }
    SharedData* data = shmat(shm_id, NULL, 0);
    data->count = 0;
    data->done = 0;
}

void child_process(int sem_id) {
    int sval = semctl(sem_id, 0, GETVAL);
    if (sval == 1) {
        key_t shm_key = ftok(SHM_FILE, KEY_SHM);
        int shm_id = shmget(shm_key, sizeof(SharedData), 0666);
        if (shm_id == -1) {
            exit(EXIT_FAILURE);
        }
        SharedData* shmaddr = (SharedData*)shmat(shm_id, NULL, 0);
        int max = shmaddr->arr[0], min = shmaddr->arr[0];
        for (int i = 1; i < shmaddr->count; i++) {
            if (shmaddr->arr[i] < min) {
                min = shmaddr->arr[i];
            } else if (shmaddr->arr[i] > max) {
                max = shmaddr->arr[i];
            }
        }
        shmaddr->min = min;
        shmaddr->max = max;
        sem_v(sem_id);
    }
}

void parent_process(int sem_id) {
    int sval = semctl(sem_id, 0, GETVAL);
    switch (sval) {
        case 0: {
            srand(time(NULL));
            int n = rand() % 10 + 1;
            int shm_size = sizeof(int) * n;
            int* set = (int*)malloc(shm_size);
            for (int i = 0; i < n; i++) {
                set[i] = rand() % 100;
                printf("%d | ", set[i]);
            }

            key_t shm_key = ftok(SHM_FILE, KEY_SHM);
            int shm_id = shmget(shm_key, sizeof(SharedData), 0666);
            if (shm_id == -1) {
                exit(EXIT_FAILURE);
            }
            SharedData* shmaddr = (SharedData*)shmat(shm_id, NULL, 0);
            shmaddr->count = n;
            for (int i = 0; i < n; i++) {
                shmaddr->arr[i] = set[i];
            }
            free(set);
            sem_v(sem_id);
            break;
        }
        case 2: {
            key_t shm_key = ftok(SHM_FILE, KEY_SHM);
            int shm_id = shmget(shm_key, sizeof(SharedData), 0666);
            if (shm_id == -1) {
                exit(EXIT_FAILURE);
            }
            SharedData* shmaddr = (SharedData*)shmat(shm_id, NULL, 0);
            printf("Min: %d, max: %d\n", shmaddr->min, shmaddr->max);
            shmaddr->done++;
            sem_p(sem_id);
            break;
        }
        default:
            break;
    }
}

void quit_parent() {
    key_t sem_key = ftok(SEM_FILE, KEY_SEM);
    key_t shm_key = ftok(SHM_FILE, KEY_SHM);
    int shm_id = shmget(shm_key, sizeof(SharedData), 0666);
    SharedData* shmaddr = (SharedData*)shmat(shm_id, NULL, 0);
    printf("\nКол-во обработанных наборов: %d\n", shmaddr->done);
    shmdt(shmaddr);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_key, 0, IPC_RMID);
    printf("Завершение родительского процесса...\n");
}

void quit_child() {
    printf("Завершение дочернего процесса...\n");
}