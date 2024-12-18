/**************************************************
 * Author:       Crzax
 * Date:         2024-10-30
 * Description:  矩阵按键相关
 **************************************************/

#include <REGX52.H>
#include "Delay.h"
#include "TrafficLight.h"
/**
  * @brief  矩阵键盘读取按键对应设定含义
  * @param  无
  * @retval KeyNumber 按下按键的对应设定含义
			如果按键按下不放，程序会停留在此函数，松手的一瞬间，返回按键对应设定含义，没有按键按下时，返回INVALID
  */
unsigned char matrixKey()	
{
	unsigned char KeyNumber=INVALID;
	
	P1=0xFE;
	P1_3=0;
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNumber=1;}
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNumber=4;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNumber=7;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNumber=10;}
	
	P1=0xFE;
	P1_2=0;
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNumber=2;}
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNumber=5;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNumber=8;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNumber=CLEAR;}
	
	P1=0xFE;
	P1_1=0;
	if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNumber=3;}
	if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNumber=6;}
	if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNumber=9;}
	if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNumber=OK;}
	
//	P1=0xFE;
//	P1_0=0;
//	if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNumber=4;}
//	if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNumber=8;}
//	if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNumber=12;}
//	if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNumber=16;}
	
	return KeyNumber;
}
