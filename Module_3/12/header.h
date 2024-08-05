#ifndef HEADER_H
#define HEADER_H

#define SHM_FILE "shmfile01"
#define SEM_FILE "semfile01"
#define KEY_SHM 'x'
#define KEY_SEM 'b'
#define SEM_MAX 2
#define ARR_MAX_SIZE 100

union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
};

typedef struct {
    int arr[ARR_MAX_SIZE];
    int count;
    int min;
    int max;
    int done;
} SharedData;

int create_sem();
void sem_p(int sem_id);
void sem_v(int sem_id);

void init_shm();
void child_process(int sem_id);
void parent_process(int sem_id);

void quit_parent();
void quit_child();

#endif