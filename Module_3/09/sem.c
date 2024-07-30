#include "sem.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

void sem_p(int semid) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = SEM_UNDO;
    semop(semid, &sem_op, 1);
}

void sem_v(int semid) {
    int sem_val = semctl(semid, 0, GETVAL);
    if (sem_val >= SEM_MAX) return;
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = SEM_UNDO;
    semop(semid, &sem_op, 1);
}

void sem_write(int semid) {
    int sem_val = semctl(semid, 0, GETVAL);
    if (sem_val >= SEM_MAX) {
        sem_p(semid);
    }
}