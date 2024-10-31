#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0Init(void);

void Timer1_Init(void);

void Timer1_SetCounter(unsigned int value);
unsigned int Timer1_GetCounter(void);
void Timer1_Run(unsigned char Flag);
#endif