#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0Init(void);

void Timer1_Init(void);

void Timer1_SetCounter(unsigned int value);
unsigned int Timer1_GetCounter(void);
void Timer1_Run(unsigned char Flag);

void Timer2_Init(void);

void Timer2_SetCounter(unsigned int value);
unsigned int Timer2_GetCounter(void);
void Timer2_Run(unsigned char Flag);
#endif