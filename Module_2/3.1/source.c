#include "header.h"

void input_digit_permissions(int *bin) {
    char str[MAX_DIGITS];
    printf("Введите число (например: 766): ");
    scanf("%s", str);
    for (int i = 0; i < 3; i++) {
        int digit = (str[i] - '0') % 10;
        *bin <<= 3;
        *bin |= digit;
    }
}

void input_letter_permissions(int *bin) {
    char str[MAX_LETTERS];
    printf("Введите права (формат: rwxrwxrwx): ");
    scanf("%s", str);
    for (int i = 0; i < 9; i++) {
        *bin <<= 1;
        if (str[i] == 'r' || str[i] == 'w' || str[i] == 'x') {
            *bin |= 1;
        } else if (str[i] == '-') {
            *bin |= 0;
        }
    }
}

int input_file(int *bin) {
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
            *bin <<= 3;
            *bin |= digit;
        }
    }
    if (pclose(pipe) == -1) {
        perror("pclose failed\n");
        return -1;
    }
    return atoi(buffer);
}

void output_bits(int bin) {
    printf("Битовое: ");
    for (int i = 8; i >= 0; i--) {
        if ((bin >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

void output_letters(int oct) {
    printf("Буквенное: ");
    for (int i = 0; i < 3; i++) {
        int digit = oct / (int)pow(10, 2 - i) % 10;
        for (int j = 0; j < 3; j++) {
            int bit = digit >> (2 - j) & 1;
            if (j == 0) {
                printf("%c", bit == 1 ? 'r' : '-');
            } else if (j == 1) {
                printf("%c", bit == 1 ? 'w' : '-');
            } else {
                printf("%c", bit == 1 ? 'x' : '-');
            }
        }
    }
    printf("\n");
}

int bin_to_oct(int bin) {
    char s[MAX_DIGITS];
    for (int i = 0; i < 3; i++) {
        s[i] = ((bin >> (3 * (2 - i))) & 7) + '0';
    }
    s[3] = '\0';
    return atoi(s);
}