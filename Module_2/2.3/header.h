#ifndef HEADER_H
#define HEADER_H

#define MAX_NUMBERS 5

double sum(int n, ...);
double sub(int n, ...);
double mult(int n, ...);
double divide(int n, ...);
double max(int n, ...);
double min(int n, ...);

double call_action(double (*operation)(int, ...), int n, double array[MAX_NUMBERS]);

#endif