#include "header.h"

void input_digit_permissions(int *permissions) {
    char str[MAX_DIGITS];
    printf("Введите число (например: 766): ");
    scanf("%s", str);
    for (int i = 0; i < 3; i++) {
        int digit = (str[i] - '0') % 10;
        *permissions <<= 3;
        *permissions |= digit;
    }
}

void input_letter_permissions(int *permissions) {
    char str[MAX_LETTERS];
    printf("Введите права (формат: rwxrwxrwx): ");
    scanf("%s", str);
    for (int i = 0; i < 9; i++) {
        *permissions <<= 1;
        if (str[i] == 'r' || str[i] == 'w' || str[i] == 'x') {
            *permissions |= 1;
        } else if (str[i] == '-') {
            *permissions |= 0;
        }
    }
}

int input_file(int *permissions) {
    char cmd[MAX_NAME] = "stat -c \"%a\" ";
    char file[MAX_NAME];
    char buffer[MAX_NAME];
    printf("Введите имя файла: ");
    scanf("%s", file);
    strcat(cmd, file);

    FILE *pipe;
    pipe = popen(cmd, "r");
    if (pipe == NULL) {
        perror("popen failed\n");
        return -1;
    }
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        for (int i = 0; i < 3; i++) {
            int digit = (buffer[i] - '0') % 10;
            *permissions <<= 3;
            *permissions |= digit;
        }
    }
    if (pclose(pipe) == -1) {
        perror("pclose failed\n");
        return -1;
    }
    return atoi(buffer);
}

void output_bits(int permissions) {
    printf("Битовое: ");
    for (int i = 8; i >= 0; i--) {
        if ((permissions >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

void output_letters(int permission) {
    printf("Буквенное: ");
    for (int i = 0; i < 3; i++) {
        
    }
    printf("\n");
}