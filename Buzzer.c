/**************************************************
 * Author:       陈震雄
 * Date:         2024-10-30
 * Description:  蜂鸣器鸣叫
 **************************************************/

#include <REGX52.H>
#include <INTRINS.H>
#include "Timer.h"
sbit Buzzer = P2^5;
unsigned char flag = 0;

/**
  * @brief  让蜂鸣器开始鸣叫，与T1计时器一起使用，1kHz
  * @param  无
  * @retval 无
  */
void setBuzzer(){
	if (flag) {
		Buzzer=!Buzzer;
		flag = 0;
	}		
}

/********************T1计时器中断处理-蜂鸣器鸣叫*************************/
void Timer1_Routine() interrupt 3 { 	// 500微秒一次中断
	TL1 = 0x66;        // 设置定时初值
    TH1 = 0xEA;        // 设置定时初值
	
	// 500微秒置1，即1kHZ振动蜂鸣器
	flag = 1;
}