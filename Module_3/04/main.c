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
    if (argc != 2) {
        printf("Программа принимает 1 аргумент - кол-во чисел!\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);
    
    pid_t pid;
    int status = 0;
    if (mkfifo(CHANNEL_PATH, 0666) == -1) {
        printf("Ошибка создания канала\n");
        exit(EXIT_FAILURE);
    }
    int fd_fifo = open(CHANNEL_PATH, O_RDWR);
    if (fd_fifo == -1) {
        printf("Ошибка открытия канала\n");
        exit(EXIT_FAILURE);
    }

    switch (pid = fork()) {
        case -1: {
            printf("Ошибка создания процесса\n");
            exit(EXIT_FAILURE);
        }
        case 0: {
            srand(time(NULL));
            for (int i = 0; i < n; i++) {
                int num = rand() % 100;
                write(fd_fifo, &num, sizeof(int));
            }
            exit(EXIT_SUCCESS);
        }
        default: {
            wait(&status);
            FILE* file = fopen(FILE_NAME, "w");
            if (file == NULL) {
                printf("Ошибка открытия выходного файла\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < n; i++) {
                int x;
                read(fd_fifo, &x, sizeof(int));
                printf("%d ", x);
                write_int(x, file);
            }
            fclose(file);
            close(fd_fifo);
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
    fputc(' ', file);
}