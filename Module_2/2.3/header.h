#ifndef HEADER_H
#define HEADER_H

#define MAX_NUMBERS 5
#define MAX_SYMBOLS 30
#define N_OPS 6

typedef double (*operation)(int n, ...);

typedef struct {
	char name[MAX_SYMBOLS];
	operation func;
} Operation;

double sum(int n, ...);
double sub(int n, ...);
double mult(int n, ...);
double divide(int n, ...);
double max(int n, ...);
double min(int n, ...);

void print_operations(Operation ops[N_OPS]);
double call_action(double (*operation)(int, ...), int n, double array[MAX_NUMBERS]);

#endif