#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void send_message(int msgid, char data[MAX_SIZE], int msgtyp) {
    msg_t msg;
    msg.mtype = msgtyp;
    strncpy(msg.mtext, data, MAX_SIZE);
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        printf("Ошибка отправки данных\n");
        exit(EXIT_FAILURE);
    }
}

msg_t receive_message(int msgid) {
    msg_t msg;
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 0, 0) == -1) {
        printf("Ошибка получения данных\n");
        exit(EXIT_FAILURE);
    }
    return msg;
}

void input_string(char str[MAX_SIZE]) {
    int ch;
    int length = 0;
    while (1) {
        length = 0;
        while ((ch = getchar()) != '\n' && ch != EOF && length < MAX_SIZE - 1) {
            str[length++] = ch;
        }
        str[length] = '\0';
        if (length == MAX_SIZE - 1) {
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        if (length > 0) {
            break;
        }
    }
}

void exit_chat(int msqid) {
    msgctl(msqid, IPC_RMID, NULL);
}