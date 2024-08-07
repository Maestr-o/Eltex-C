#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main() {
    int sem_id = create_sem();
    int shm_fd = init_shm();
    pid_t pid;
    switch (pid = fork()) {
        case -1: {
            printf("Ошибка создания дочернего процесса\n");
            exit(EXIT_FAILURE);
        }
        case 0: {
            signal(SIGINT, quit_child);
            while (1) {
                child_process(sem_id, shm_fd);
                sleep(1);
            }
        }
        default: {
            signal(SIGINT, quit_parent);
            while (1) {
                parent_process(sem_id, shm_fd);
                sleep(1);
            }
        }
    }
    return EXIT_SUCCESS;
}