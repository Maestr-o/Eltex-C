#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <wait.h>
#include <signal.h>
#include <poll.h>

#define MAX_CLIENTS 5

void dostuff(int);

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void printusers(int n) {
    if (n - 1) {
        printf("%d user online\n", n - 1);
    } else {
        printf("No user online\n");
    }
}

int sum(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mult(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    return a / b;
}

int sockfd;

void handle_sigint(int sig) {
    printf("\nCaught signal %d, closing socket and exiting...\n", sig);
    close(sockfd);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    int newsockfd;                           // дескриптор нового сокета
    int portno;                              // номер порта
    socklen_t clilen;                        // размер адреса клиента типа socklen_t
    struct sockaddr_in serv_addr, cli_addr;  // структура сокета сервера и клиента
    struct pollfd poll_fds[MAX_CLIENTS + 1]; // массив дескрипторов poll
    int nfds = 1;                            // начинаем с одного серверного сокета

    printf("TCP SERVER DEMO\n");
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(EXIT_FAILURE);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    signal(SIGINT, handle_sigint);

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");

    listen(sockfd, MAX_CLIENTS);
    clilen = sizeof(cli_addr);

    poll_fds[0].fd = sockfd;
    poll_fds[0].events = POLLIN;
    for (int i = 1; i <= MAX_CLIENTS; i++) {
        poll_fds[i].fd = -1;
    }

    while (1) {
        int activity;
        if ((activity = poll(poll_fds, nfds, -1)) < 0) error("ERROR on poll");

        if (poll_fds[0].revents & POLLIN) {
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
            if (newsockfd < 0) error("ERROR on accept");
            if (nfds < MAX_CLIENTS + 1) {
                poll_fds[nfds].fd = newsockfd;
                poll_fds[nfds].events = POLLOUT;
                nfds++;
                struct hostent *hst;
                hst = gethostbyaddr((char *)&cli_addr.sin_addr, 4, AF_INET);
                printf("+%s [%s] new connect!\n", (hst) ? hst->h_name : "Unknown host", inet_ntoa(cli_addr.sin_addr));
                printusers(nfds);
            } else {
                printf("Too many clients connected\n");
                close(newsockfd);
            }
        }

        for (int i = 1; i < nfds; i++) {
            if (poll_fds[i].revents & POLLOUT) {
                dostuff(poll_fds[i].fd);
                close(poll_fds[i].fd);
                poll_fds[i] = poll_fds[nfds - 1];
                nfds--;
                printf("-disconnect\n");
                printusers(nfds);
            }
        }
    }
    close(sockfd);
    return 0;
}

void dostuff(int sock) {
    int bytes_recv;
    int a, b, res;
    int err = 0;
    char sign;
    char buff[20 * 1024];
    memset(buff, 0, sizeof(buff));
#define str1 "Enter 1 number\r\n"
#define str2 "Enter operation (+-/*)\r\n"
#define str3 "Enter 2 number\r\n"
#define errstr "Error. Check input data\r\n"
    write(sock, str1, sizeof(str1));
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0) error("ERROR reading from socket");
    a = atoi(buff);

    memset(buff, 0, sizeof(buff));
    write(sock, str2, sizeof(str2));
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0) error("ERROR reading from socket");
    sign = buff[0];

    memset(buff, 0, sizeof(buff));
    write(sock, str3, sizeof(str3));
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0) error("ERROR reading from socket");
    b = atoi(buff);
    
    switch (sign) {
        case '+':
            res = sum(a, b);
            break;
        case '-':
            res = sub(a, b);
            break;
        case '*':
            res = mult(a, b);
            break;
        case '/': {
            if (b == 0) err = 1;
            else res = divide(a, b);
            break;
        }
        default:
            err = 1;
            break;
    }

    if (!err) {
        snprintf(buff, sizeof(buff), "%d\n", res);
    } else {
        snprintf(buff, sizeof(buff), "%s", errstr);
    }
    buff[strlen(buff)] = '\n';
    write(sock, &buff[0], strlen(buff) + 1);
}