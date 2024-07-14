#include "header.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Использование: ([IP-адрес шлюза] [маска подсети] [кол-во пакетов])\n");
        return 1;
    }
    start(argv[1], argv[2], argv[3]);
    return 0;
}