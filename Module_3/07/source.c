#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mqueue.h>

void create_queue() {
    exit_chat();
    
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    int mqid = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (mqid == -1) {
        perror("Ошибка создания очереди");
        exit(EXIT_FAILURE);
    }
    mq_close(mqid);
}

void send_message(const char* data, unsigned int priority) {
    mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY);
    if (mq == -1) {
        perror("Ошибка открытия очереди");
        exit(EXIT_FAILURE);
    }
    if (mq_send(mq, data, strlen(data) + 1, priority) == -1) {
        perror("Ошибка отправки данных");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }
    mq_close(mq);
}

void receive_message(char* text, unsigned int* priority) {
    mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY);
    struct mq_attr attr;
    if (mq == -1) {
        perror("Ошибка открытия очереди");
        exit(EXIT_FAILURE);
    }
    if (mq_getattr(mq, &attr) == -1) {
        perror("Ошибка получения атрибутов");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }
    if (mq_receive(mq, text, attr.mq_msgsize, priority) == -1) {
        perror("Ошибка получения данных");
        mq_close(mq);
        exit(EXIT_FAILURE);
    }
    mq_close(mq);
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

void exit_chat() {
    mq_unlink(QUEUE_NAME);
}