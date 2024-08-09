#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    char buf[BUF_SIZE];

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        return EXIT_FAILURE;
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(FIRST_PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    if (bind(sock_fd, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка привязки сокета");
        close(sock_fd);
        return EXIT_FAILURE;
    }

    char str[BUF_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    printf("Клиент запущен. Ожидание сообщений...\n");
    while (strcmp(str, END_MSG) != 0) {
        memset(buf, 0, BUF_SIZE);
        if (recvfrom(sock_fd, buf, BUF_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len) < 0) {
            perror("Ошибка получения сообщения");
            close(sock_fd);
            exit(EXIT_FAILURE);
        }
        printf("* %s\n-> ", buf);
        if (strcmp(buf, END_MSG) == 0) break;
        input_string(str);
        if (sendto(sock_fd, str, BUF_SIZE, 0, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
            perror("Ошибка отправки сообщения");
            close(sock_fd);
            exit(EXIT_FAILURE);
        };
    }
    close(sock_fd);

    return EXIT_SUCCESS;
}