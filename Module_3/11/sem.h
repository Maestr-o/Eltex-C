#ifndef SEM_H
#define SEM_H

#include <semaphore.h>

#define SEM_MAX 2
#define SEM_NAME "/semaphore_0001"

void sem_create();
void sem_p();
void sem_v();
void sem_write();

#endif