#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 4
#define MAX_LETTERS 10
#define MAX_NAME 255

void input_digit_permissions(int *permissions);
void input_letter_permissions(int *permissions);
int input_file(int *permissions);
void output_bits(int permissions);
void output_letters(int permissions);
int bin_to_oct(int permissions);

#endif