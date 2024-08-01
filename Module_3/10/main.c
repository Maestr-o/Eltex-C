#include "sem.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <time.h>
#include <fcntl.h>

#define CHANNEL_PATH "/tmp/fifo0001.1"
#define FILE_NAME "output.txt"

void write_int(int x, FILE* file);

int main(int argc, char* argv[]) {
    unlink(CHANNEL_PATH);
    sem_unlink(SEM_NAME);

    if (argc != 2) {
        printf("Программа принимает 1 аргумент - кол-во чисел!\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);
    
    if (mkfifo(CHANNEL_PATH, 0666) == -1) {
        printf("Ошибка создания канала\n");
        exit(EXIT_FAILURE);
    }
    int fd_fifo = open(CHANNEL_PATH, O_RDWR);
    if (fd_fifo == -1) {
        printf("Ошибка открытия канала\n");
        exit(EXIT_FAILURE);
    }

    sem_create();
    pid_t pid;
    switch (pid = fork()) {
        case -1: {
            printf("Ошибка создания процесса\n");
            exit(EXIT_FAILURE);
        }
        case 0: {
            while (1) {
                sleep(1);
                if (access(CHANNEL_PATH, F_OK) != 0) {
                    printf("Завершение дочернего процесса...\n");
                    exit(EXIT_SUCCESS);
                }
                sem_p();
                FILE *file = fopen(FILE_NAME, "r");
                if (file == NULL) {
                    printf("Ошибка открытия файла для чтения\n");
                    exit(EXIT_FAILURE);
                }
                int x;
                while (fscanf(file, "%d", &x) != EOF) {
                    printf("Чтение потомком: %d\n", x);
                }
                fclose(file);
                write(fd_fifo, &x, sizeof(int));
                sem_v();
            }
            exit(EXIT_SUCCESS);
        }
        default: {
            srand(time(NULL));
            for (int i = 0; i < n; i++) {
                int num = rand() % 100;
                sem_p();
                FILE* file = fopen(FILE_NAME, "w");
                if (file == NULL) {
                    printf("Ошибка открытия выходного файла\n");
                    exit(EXIT_FAILURE);
                }
                write_int(num, file);
                printf("Записано родителем: %d\n", num);
                fclose(file);
                sem_v();
                sleep(2);
            }
            close(fd_fifo);
            sem_unlink(SEM_NAME);
            unlink(CHANNEL_PATH);
            exit(EXIT_SUCCESS);
        }
    }
    return EXIT_SUCCESS;
}

void write_int(int x, FILE* file) {
    if (x == 0) {
        fputc('0', file);
    } else {
        char buffer[12];
        int i = 0;
        if (x < 0) {
            fputc('-', file);
            x = -x;
        }
        while (x > 0) {
            buffer[i++] = (x % 10) + '0';
            x /= 10;
        }
        while (i > 0) {
            fputc(buffer[--i], file);
        }
    }
}