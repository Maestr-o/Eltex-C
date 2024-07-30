#ifndef SEM_H
#define SEM_H

union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo *__buf;
};

void sem_p(int semid);
void sem_v(int semid);

#endif