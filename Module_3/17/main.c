#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define PORT 60410
#define IP_ADDRESS "127.0.0.1"
#define DUMP_FILE "dump.bin"
#define BUF_SIZE 1024
#define UDP_HEADER_SIZE 8

int fd, sock_fd;

void print_packet(char buf[BUF_SIZE], int offset);
void quit();

int main() {
    struct sockaddr_in sockaddr;
    socklen_t addrlen;
    char buf[BUF_SIZE];
    signal(SIGINT, quit);

    if ((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(PORT);
    sockaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    addrlen = sizeof(sockaddr);
    if (bind(sock_fd, (const struct sockaddr*)&sockaddr, addrlen) < 0) {
        perror("Ошибка привязки сокета");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    fd = open(DUMP_FILE, O_CREAT | O_WRONLY, 0666);
    if (fd < 0) {
        printf("Ошибка открытия выходного файла\n");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    while (1) {
        memset(&buf[0], 0, BUF_SIZE);
        ssize_t bytes_received = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr, &addrlen);
        if (bytes_received > 0) {
            struct iphdr *ip_header = (struct iphdr *)buf;
            struct udphdr *udp_header = (struct udphdr *)(buf + (ip_header->ihl * 4));
            if (ntohs(udp_header->dest) == PORT) {
                write(fd, buf, bytes_received);
                int offset = ip_header->ihl * 4 + UDP_HEADER_SIZE;
                print_packet(buf, offset);
            }
        }
    }
    return EXIT_SUCCESS;
}

void print_packet(char buf[BUF_SIZE], int offset) {
    printf("Размер заголовка (IP+UDP): %d байт\n", offset);
    printf("Сообщение:\n");
    for (int i = offset; buf[i] >= 32 && buf[i] <= 126; i++) {
        printf("%c", buf[i]);
    }
    printf("\n----------\n");
}
void quit() {
    printf("Завешение работы...\n");
    close(fd);
    close(sock_fd);
    exit(EXIT_SUCCESS);
}