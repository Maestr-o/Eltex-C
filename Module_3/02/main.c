#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
    pid_t pid;
    int rv = 0;

    while (1) {
        if (WEXITSTATUS(rv) != 0) {
            printf("Предыдущая программа завершилась с ошибкой\n");
            rv = 0;
        }

        printf(">> ");
        char cmd[255];
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        if (strcmp(cmd, "exit") == 0) exit(EXIT_SUCCESS);
        switch (pid = fork()) {
            case -1: {
                printf("Ошибка создания процесса!\n");
                exit(EXIT_FAILURE);
            }
            case 0: {
                char *args[255];
                int i = 0;
                char *token = strtok(cmd, " ");
                while (token != NULL && i < 254) {
                    args[i++] = token;
                    token = strtok(NULL, " ");
                }
                args[i] = NULL;
                execv(args[0], args);

                printf("Ошибка запуска команды \"%s\"\n", cmd);
                exit(EXIT_FAILURE);
            }
            default: {
                wait(&rv);
            }
        }
    }
    return EXIT_SUCCESS;
}