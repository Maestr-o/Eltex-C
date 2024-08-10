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
#include <fcntl.h>

// функция обслуживания подключившихся пользователей
void dostuff(int);
// функция обработки ошибок
void error(const char *msg) {
    perror(msg);
    exit(1);
}
// количество активных пользователей
int nclients = 0;
// печать количества активных пользователей
void printusers() {
    if (nclients) {
        printf("%d user online\n", nclients);
    }
    else {
        printf("No user online\n");
    }
}
// функции обработки данных
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

// обработчик сигнала SIGCHLD для корректного подсчета кол-ва активных пользователей
void sigchld_handler() {
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        printf("-disconnect\n");
        nclients--;
        printusers();
    }
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd;                  // дескрипторы сокетов
    int portno;                             // номер порта
    int pid;                                // id номер потока
    socklen_t clilen;                       // размер адреса клиента типа socklen_t
    struct sockaddr_in serv_addr, cli_addr; // структура сокета сервера и клиента
    printf("TCP SERVER DEMO\n");
    // ошибка, если мы не указали порт
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    // Шаг 1 - создание сокета
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    // Шаг 2 - связывание сокета с локальным адресом
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // сервер принимает подключения на все IP-адреса
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
    // Шаг 3 - ожидание подключений, размер очереди - 5
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // Шаг 4 - извлекаем сообщение из очереди (цикл извлечения запросов на подключение)
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) error("ERROR on accept");
        nclients++;
        // вывод сведений о клиенте
        struct hostent *hst;
        hst = gethostbyaddr((char *)&cli_addr.sin_addr, 4, AF_INET);
        printf("+%s [%s] new connect!\n", (hst) ? hst->h_name : "Unknown host", inet_ntoa(cli_addr.sin_addr));
        printusers();
        pid = fork();
        if (pid < 0) error("ERROR on fork");
        if (pid == 0) {
            close(sockfd);
            dostuff(newsockfd);
            exit(0);
        } else {
            signal(SIGCHLD, sigchld_handler);
            close(newsockfd);
        }
    }
    close(sockfd);
    return 0;
}

void dostuff(int sock) {
    int bytes_recv; // размер принятого сообщения
    int a, b, res;  // переменные для вычисления
    int err = 0;    // флаг ошибки
    char sign;      // операция
    char buff[20 * 1024];
#define startstr "Choose mode: calc/file\r\n"
#define filestr "Enter path to the file: "
#define str1 "Enter 1 number\r\n"
#define str2 "Enter operation (+-/*)\r\n"
#define str3 "Enter 2 number\r\n"
#define errstr "Error. Check input data\r\n"
    write(sock, startstr, sizeof(startstr));
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0) error("ERROR reading from socket");
    if (!strcmp(buff, "calc")) { // калькулятор
        write(sock, str1, sizeof(str1));
        bytes_recv = read(sock, &buff[0], sizeof(buff));
        if (bytes_recv < 0) error("ERROR reading from socket");
        a = atoi(buff);

        write(sock, str2, sizeof(str2));
        bytes_recv = read(sock, &buff[0], sizeof(buff));
        if (bytes_recv < 0) error("ERROR reading from socket");
        sign = buff[0];

        write(sock, str3, sizeof(str3));
        bytes_recv = read(sock, &buff[0], sizeof(buff));
        if (bytes_recv < 0) error("ERROR reading from socket");
        b = atoi(buff);
        
        // вычисление
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
        write(sock, &buff[0], sizeof(buff));
    } else if (!strcmp(buff, "file")) { // получение файла
        bzero(buff, sizeof(buff));
        while ((bytes_recv = read(sock, buff, sizeof(buff))) > 0) {
            printf("%s", buff);
            bzero(buff, sizeof(buff));
        }
        printf("\n");
    }
}