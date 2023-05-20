#ifndef UART_H
#define UART_H

void print(const char *str);
int print_idec(int n);
void print_ihex(unsigned n);
void print_ibin(unsigned n);
void print_all(unsigned n);

#endif