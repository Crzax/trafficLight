/**************************************************
 * Author:       陈震雄
 * Date:         2024-10-31
 * Description:  外部中断0相关
 **************************************************/

#include <REGX52.H>


void Int0_Init(void) {
	IT0 = 1;
	IE0 = 0;
	EX0=1;
	EA=1;
	PX0=1;
}

//void Int0_Routine(void) interrupt 0
//{
//	
//}