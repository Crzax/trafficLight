/**************************************************
 * Author:       陈震雄
 * Date:         2024-10-30
 * Description:  蜂鸣器鸣叫
 **************************************************/

#include <REGX52.H>
#include <INTRINS.H>

sbit Buzzer = P2^5;
unsigned char buzzerFlag = 0;

/**
  * @brief  让蜂鸣器开始鸣叫，与T1计时器一起使用，1kHz
  * @param  无
  * @retval 无
  */
void setBuzzer(){
	if (buzzerFlag) {
		Buzzer=!Buzzer;
		buzzerFlag = 0;
	}		
}
