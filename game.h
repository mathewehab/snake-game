#ifndef GAME_H
#define GAME_H
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "bsp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_RED (1U << 1)
#define SCREENSIZE 20
#define WINSCORE 50

#define MAXCALDA 399

void setUp();
void map_draw();
void input(char comand);
void logic();
void delay_ms(int n);
void mainloop();

#endif