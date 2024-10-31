#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0Init(void);

void Timer1Init(void);

void Timer2_Init(void);
void Timer2_SetCounter(unsigned int value);
unsigned int Timer2_GetCounter(void);
void Timer2_Run(unsigned char Flag);
#endif