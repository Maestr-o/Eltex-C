#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void start(char gateway[IP_SYMBOLS], char mask[IP_SYMBOLS], char n[MAX_DIGITS_N]) {
    int num_packets = atoi(n);
    uint32_t gateway_ip = ip_to_uint32(gateway);
    uint32_t subnet_mask = ip_to_uint32(mask);
    uint32_t network_address = compute_subnet(gateway_ip, subnet_mask);

    srand(time(NULL));
    int packets_in_subnet = 0;
    int packets_outside_subnet = 0;

    for (int i = 0; i < num_packets; i++) {
        uint32_t random_ip = generate_random_ip();
        uint32_t random_ip_network = compute_subnet(random_ip, subnet_mask);

        if (random_ip_network == network_address) {
            packets_in_subnet++;
        } else {
            packets_outside_subnet++;
        }
    }

    printf("Всего пакетов: %d\n", num_packets);
    printf("Пакетов в подсети: %d (%.2f%%)\n", packets_in_subnet, (100.0 * packets_in_subnet / num_packets));
    printf("Пакетов не в подсети: %d (%.2f%%)\n", packets_outside_subnet, (100.0 * packets_outside_subnet / num_packets));
}

uint32_t ip_to_uint32(const char *ip_str) {
    uint32_t ip = 0;
    int octet;
    char *token;
    char ip_copy[16];

    strncpy(ip_copy, ip_str, 16);
    token = strtok(ip_copy, ".");

    for (int i = 0; i < 4; i++) {
        if (token != NULL) {
            octet = atoi(token);
            ip = (ip << 8) | (octet & 0xFF);
            token = strtok(NULL, ".");
        } else {
            ip = (ip << 8);
        }
    }
    return ip;
}

uint32_t compute_subnet(uint32_t ip, uint32_t mask) {
    return ip & mask;
}

uint32_t generate_random_ip() {
    return (rand() % 256) | ((rand() % 256) << 8) | ((rand() % 256) << 16) | ((rand() % 256) << 24);
}