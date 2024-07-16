#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 4
#define MAX_LETTERS 10
#define MAX_NAME 255

void input_digit_permissions(int *bin);
void input_letter_permissions(int *bin);
int input_file(int *bin);
void output_bits(int bin);
void output_letters(int bin);
int bin_to_oct(int bin);
void change_rights(int *bin, char cmd[MAX_LETTERS]);

#endif