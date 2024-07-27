#ifndef HEADER_H
#define HEADER_H

#define MSG_KEY 124
#define MAX_SIZE 255
#define EXIT_TYPE 2

typedef struct {
    long mtype;
    char mtext[MAX_SIZE];
} msg_t;

void send_message(int msgid, char data[MAX_SIZE], int msgtyp);
msg_t receive_message(int msgid);
void input_string(char str[MAX_SIZE]);
void exit_chat(int msqid);

#endif