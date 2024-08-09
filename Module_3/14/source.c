#include "header.h"

#include <stdio.h>

void input_string(char str[BUF_SIZE]) {
    int ch;
    int length = 0;
    while (1) {
        length = 0;
        while ((ch = getchar()) != '\n' && ch != EOF && length < BUF_SIZE - 1) {
            str[length++] = ch;
        }
        str[length] = '\0';
        if (length == BUF_SIZE - 1) {
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        if (length > 0) {
            break;
        }
    }
}