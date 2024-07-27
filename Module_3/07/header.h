#ifndef HEADER_H
#define HEADER_H

#include "mqueue.h"

#define QUEUE_NAME "/queue_chat_01"
#define MAX_SIZE 256
#define NORM_PRIORITY 1
#define EXIT_PRIORITY 2

void create_queue();
void send_message(const char* data, unsigned int priority);
void receive_message(char* text, unsigned int* priority);
void input_string(char str[MAX_SIZE]);
void exit_chat();

#endif