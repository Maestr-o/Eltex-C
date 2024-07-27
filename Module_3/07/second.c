#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <signal.h>

void handle_sigint(int sig);

int main() {
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        printf("Не удалось установить обработчик для SIGINT.\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        char answer[MAX_SIZE];
        unsigned int priority;
        receive_message(answer, &priority);
        if (priority == NORM_PRIORITY) {
            printf("Получено: %s\n", answer);
        } else if (priority == EXIT_PRIORITY) {
            printf("\nЗакрытие чата...\n");
            exit_chat();
            exit(EXIT_SUCCESS);
        }

        printf("Новое сообщение: ");
        char text[MAX_SIZE];
        input_string(text);
        send_message(text, NORM_PRIORITY);
    }
    return EXIT_SUCCESS;
}

void handle_sigint(int sig) {
    printf("\nПолучен сигнал SIGINT (Ctrl+C). Закрытие чата...\n");
    char data[MAX_SIZE] = "0";
    send_message(data, EXIT_PRIORITY);
    exit(EXIT_SUCCESS);
}