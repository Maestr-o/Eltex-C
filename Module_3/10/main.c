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
    remove(FILE_NAME);

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
    fclose(fopen(FILE_NAME, "w"));

    sem_create();
    pid_t pid;
    switch (pid = fork()) {
        case -1: {
            printf("Ошибка создания процесса\n");
            exit(EXIT_FAILURE);
        }
        case 0: {
            for (int i = 0; i < n; i++) {
                int num = rand() % 100;
                write(fd_fifo, &num, sizeof(int));
                
                sleep(1);

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
                sem_v();
            }
            remove(FILE_NAME);
            close(fd_fifo);
            sem_unlink(SEM_NAME);
            unlink(CHANNEL_PATH);
            printf("Завершение дочернего процесса...\n");
            exit(EXIT_SUCCESS);
        }
        default: {
            srand(time(NULL));
            int i = 0;
            while (i < n) {
                int num;
                read(fd_fifo, &num, sizeof(int));

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
                i++;
            }
            printf("Завершение родительского процесса...\n");
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