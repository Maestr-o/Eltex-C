#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int msqid = -1;

void handle_sigint(int sig);

int main() {
    msqid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msqid == -1) {
        printf("Ошибка создания очереди\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        printf("Не удалось установить обработчик для SIGINT.\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        printf("Новое сообщение: ");
        char text[MAX_SIZE];
        input_string(text);
        send_message(msqid, text, 1);

        printf("Ждём ответ...\n");
        msg_t msg = receive_message(msqid);
        if (msg.mtype == EXIT_TYPE) {
            printf("Получен сигнал завершения работы чата\n");
            exit_chat(msqid);
            exit(EXIT_SUCCESS);
        }
        printf("Получено: %s\n", msg.mtext);
    }

    return EXIT_SUCCESS;
}

void handle_sigint(int sig) {
    printf("\nПолучен сигнал SIGINT (Ctrl+C). Закрытие чата...\n");
    char data[MAX_SIZE] = "0";
    send_message(msqid, data, EXIT_TYPE);
    exit_chat(msqid);
    exit(EXIT_SUCCESS);
}