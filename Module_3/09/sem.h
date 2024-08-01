#ifndef SEM_H
#define SEM_H

#define SEM_MAX 2

union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo *__buf;
};

int sem_write(int semid);
void sem_p(int semid);
void sem_v(int semid);

#endif