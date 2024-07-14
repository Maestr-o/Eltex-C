#ifndef HEADER_H
#define HEADER_H

#define IP_SYMBOLS 16
#define MAX_DIGITS_N 8

#include <stdint.h>

void start(char gateway[IP_SYMBOLS], char mask[IP_SYMBOLS], char n[MAX_DIGITS_N]);
uint32_t ip_to_uint32(const char *ip_str);
uint32_t compute_subnet(uint32_t ip, uint32_t mask);
uint32_t generate_random_ip();

#endif