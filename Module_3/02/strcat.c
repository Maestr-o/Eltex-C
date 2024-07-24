#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Введите строки!\n");
        exit(EXIT_FAILURE);
    }
    char res[1000] = "";
    for (int i = 1; i < argc; i++) {
        strcat(res, argv[i]);
    }
    printf("Ответ: %s\n", res);
    return EXIT_SUCCESS;
}