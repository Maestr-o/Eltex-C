#ifndef HEADER_H
#define HEADER_H

#define MAX_NUMBERS 5

double sum(int n, ...);
double sub(int n, ...);
double mult(int n, ...);
double divide(int n, ...);
double max(int n, ...);
double min(int n, ...);

double call_sum(int n, double array[MAX_NUMBERS]);
double call_sub(int n, double array[MAX_NUMBERS]);
double call_mult(int n, double array[MAX_NUMBERS]);
double call_div(int n, double array[MAX_NUMBERS]);
double call_max(int n, double array[MAX_NUMBERS]);
double call_min(int n, double array[MAX_NUMBERS]);

#endif