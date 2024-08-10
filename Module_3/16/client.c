#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int my_sock, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buff[1024];
    printf("TCP DEMO CLIENT\n");
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    // извлечение порта
    portno = atoi(argv[2]);
    // Шаг 1 - создание сокета
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0) error("ERROR opening socket");
    // извлечение хоста
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    // заполнение структуры serv_addr
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    // установка порта
    serv_addr.sin_port = htons(portno);
    // Шаг 2 - установка соединения
    if (connect(my_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR connecting");
    // Шаг 3 - чтение и передача сообщений
    while ((n = recv(my_sock, &buff[0], sizeof(buff) - 1, 0)) > 0) {
        buff[n] = 0;
        printf("S=>C:%s", buff);
        printf("S<=C:");
        fgets(&buff[0], sizeof(buff) - 1, stdin);
        if (!strcmp(&buff[0], "quit\n")) {
            break;
        } else if (!strcmp(&buff[0], "file\n")) {
            send(my_sock, &buff[0], strlen(&buff[0]) - 1, 0);
            printf("Введите путь до файла: ");
            char path[255];
            fgets(&path[0], sizeof(path) - 1, stdin);
            path[strcspn(path, "\n")] = '\0';
            int fd = open(path, O_RDONLY);
            if (fd < 0) {
                printf("Ошибка открытия файла\n");
                break;
            }
            while ((n = read(fd, buff, sizeof(buff))) > 0) {
                send(my_sock, buff, n, 0);
            }
            close(fd);
            break;
        } else if (!strcmp(&buff[0], "calc\n")) {
            send(my_sock, &buff[0], strlen(&buff[0]) - 1, 0);
        } else {
            send(my_sock, &buff[0], strlen(&buff[0]), 0);
        }
    }
    printf("Exit...\n");
    close(my_sock);
    return 0;
}