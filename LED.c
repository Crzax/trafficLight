/**************************************************
 * Author:       陈震雄
 * Date:         2024-10-29
 * Description:  与LED操作有关
 **************************************************/

#include <REGX52.H>
#include "Delay.h"

// 数码管段选表
unsigned char code NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00};

/**
  * @brief  数码管显示
  * @param  Location: 指定8个数码管的一个
  * @param  Number: 该位置显示的数字
  * @retval 无
  */
void nixie(unsigned char Location, Number)
{
	switch(Location)		
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	
	
	// 清零消影
	delay(1);				
	P0=0x00;				
}

/**
  * @brief  输入数字，选择在前半部分显示还是后半部分
  * @param  无
  * @retval 无
  */
void showNum(unsigned char loc, num) 
{
	
	if (loc == 1){
		if (num == 666) {
			nixie(1,10);
			nixie(2,10);
			nixie(3,10);
		}else{
			nixie(1,num/100);
			num %= 100;
			nixie(2,num/10);
			nixie(3,num%10);
//			nixie(1,num/10);
//			nixie(2,num%10);
		}
	} else {
		if (num == 666) {
			nixie(1,10);
			nixie(2,10);
			nixie(3,10);
		}else{
			nixie(5,num/100);
			num %= 100;
			nixie(6,num/10);
			nixie(7,num%10);
//			nixie(5,num/10);
//			nixie(6,num%10);
		}
	}
}