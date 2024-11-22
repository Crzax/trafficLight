/**************************************************
 * Author:       Crzax
 * Date:         2024-10-29
 * Description:  交通灯实现文件
 **************************************************/
#include "TrafficLight.h"
#include <REGX52.H>
#include "Timer.h"
#include "LED.h"
#include "Buzzer.h"
#include "Key.h"
#include "MatrixKey.h"
#include "IR.h"
#include "DS18B20.h"
#include "Delay.h"
/**************************交通灯************************************/
// 交通灯结构体
typedef struct {
    unsigned char greenLightPin;	// 绿灯对应的P2位寄存器
    unsigned char redLightPin;		// 红灯对应的P2位寄存器
    unsigned int time;				// 所剩时间
    unsigned char flag;				// 标识红/绿/黄灯
	unsigned char isBlink;			// 是否闪烁
} TrafficLight;

unsigned char isSet = 0;		// 是否进入设置倒计时模式
sbit motor = P1^0;				// 电风扇
sbit Buzzer = P2^5;					// 蜂鸣器
extern float t;						// 当前温度的值
extern unsigned char buzzerFlag;	// 是否开始叫的一个判断依据
// 置黄灯
void setYellow(TrafficLight* self) {
    P2 &= ~(1 << self->greenLightPin);  // 打开绿灯
    P2 &= ~(1 << self->redLightPin);    // 打开红灯
    self->flag = YELLOW;
    self->time = YELLOWTIME;
}

// 置绿灯
void setGreen(TrafficLight* self) {
    P2 &= ~(1 << self->greenLightPin);   // 打开绿灯
    P2 |= 1 << self->redLightPin;    // 关闭红灯
    self->flag = GREEN;
    self->time = GREENTIME;
}

// 置红灯
void setRed(TrafficLight* self) {
    P2 |= 1 << self->greenLightPin;  // 关闭绿灯
    P2 &= ~(1 << self->redLightPin);     // 打开红灯
    self->flag = RED;
    self->time = REDTIME;
}

// 闪烁
void blink(TrafficLight* self) {
	if (self->flag==RED) {
		P2 ^= 1 << self->redLightPin;
	} else {
		P2 ^= 1 << self->greenLightPin;
	}
}

// 南北向交通灯
TrafficLight SN = {0, 1, GREENTIME, GREEN,0};

// 东西向交通灯
TrafficLight EW = {6, 7, REDTIME, RED,0};

/**************************初始化函数************************************/
void init() {
    setGreen(&SN);
    setRed(&EW);
	Timer0Init();
	IR_Init();
	Buzzer = 0;		// 防止蜂鸣器一通电就响
	motor = 0;		// 防止风扇一开始就转
	DS18B20_ConvertT();		//上电先转换一次温度，防止第一次读数据错误
	delay(1000);
}

/**************************主函数************************************/
void main() {
	unsigned char keyNum = 0;
	unsigned char matrixKeyNum = INVALID;	
	unsigned char IRNum = INVALID;
	unsigned char i = 0;
	float T = 0;
	
    init();

    while(1) {
		/**************************低于3s闪烁，否则正常(黄灯除外)**************************/
		if (SN.isBlink) {	
			showNum(1,666);
		} else {
			showNum(1, SN.time);
		}
		if (EW.isBlink) {	
			showNum(2,666);
		} else {
			showNum(2, EW.time);
		}
		
		/**************************绿灯&&低于BUZZERTIME开始鸣叫**************************/
		if (SN.flag==GREEN&&SN.time<=BUZZERTIME) {
			setBuzzer();
		}
		
		if (EW.flag==GREEN&&EW.time<=BUZZERTIME) {
			setBuzzer();
		}

		/*************紧急情况，延长红灯时间3秒(对应另一个路口它的状态也延长三秒)****************/
		keyNum = Key();
		if (keyNum==1) {
			SN.time += 3;
			EW.time += 3;
		}
		
		/**************************温度过高，开始吹风扇**************************/
		T=getT();	//读取温度
		if (T>TH) 
			motor = 1;
		else
			motor = 0;
		/**************************设置倒计时模式(矩阵键盘)**************************/
		if (keyNum == 2 && SN.flag!=YELLOW) {
			isSet = 1;
			SN.time = 0;
			// 第二个数码管不显示
			showNum(2,666);

			// 获取两个输入
			for(i=0;i<3;) {
				while(1) {
					showNum(1, SN.time);
					matrixKeyNum =  matrixKey();
					if (matrixKeyNum<INVALID) break; 
				}
				if (i<2&&matrixKeyNum<=10) {
					SN.time *= 10;
					SN.time += matrixKeyNum % 10;
					SN.time %= 100;
					++i;
				}
				if (matrixKeyNum==ADDONE) {SN.time++; SN.time %= 100;}
				if (matrixKeyNum==SUBONE) {SN.time--; SN.time %= 100;}
				if (matrixKeyNum==OK) break;
				if (matrixKeyNum==CLEAR) {
					SN.time = 0;
					i=0;
				}
				matrixKeyNum = INVALID;
			}
			
			if (SN.flag==GREEN) {
				// 南北绿灯，则东西只能红灯
				EW.flag=RED;
				EW.time = SN.time + YELLOWTIME;
			} else {
				// 南北红灯，东西黄灯
				if (SN.time <= YELLOWTIME) {
					EW.flag = YELLOW;
					EW.time = SN.time;
				} else {
					// 南北红灯，东西绿灯
					EW.flag = GREEN;
					EW.time = SN.time - YELLOWTIME;
				}
			}
			isSet = 0;
		}
		/**************************设置倒计时模式(红外线遥控器)**************************/
		if (IR_GetDataFlag() && IR_GetCommand() == IR_MODE) {
			isSet = 1;
			SN.time = 0;
			
			// 第二个数码管不显示
			showNum(2,666);
			// 获取两个输入
			for(i=0;i<3;) {
				while(1) {
					showNum(1, SN.time);
					IRNum =  IR_GetNumber();
					if (IRNum<INVALID) break; 
				}
				if (i<2 && IRNum<10) {
					SN.time *= 10;
					SN.time += IRNum;
					SN.time %= 100;
					++i;
				}
				if (IRNum==ADDONE) {SN.time++; SN.time %= 100;}
				if (IRNum==SUBONE) {SN.time--; SN.time %= 100;}
				if (IRNum==OK) {SN.time %= 100; break;}
				if (IRNum==CLEAR) {
					SN.time = 0;
					i=0;
				}
				IRNum = INVALID;
			}
			
			if (SN.flag==GREEN) {
				// 南北绿灯，则东西只能红灯
				EW.flag=RED;
				EW.time = SN.time + YELLOWTIME;
			} else {
				// 南北红灯，东西黄灯
				if (SN.time <= YELLOWTIME) {
					EW.flag = YELLOW;
					EW.time = SN.time;
				} else {
					// 南北红灯，东西绿灯
					EW.flag = GREEN;
					EW.time = SN.time - YELLOWTIME;
				}
			}
			isSet = 0;
		}
    }
}

/********************T0计时器中断处理-交通灯LED/数码管*************************/
void Timer0_Routine() interrupt 1 {	// 500us一次中断
    static unsigned int T0Count = 0;
	static unsigned int waitForGetT = 0;	// 1500次，即750ms，用于读取温度值
	TL0 = 0x33;        // 设置定时初值
    TH0 = 0xFE;        // 设置定时初值
	buzzerFlag = 1;    // 500微秒置1，即1kHZ振动蜂鸣器
	// 读取温度值
	waitForGetT++;
	if (waitForGetT>=1500) {
		waitForGetT = 0;
		t = DS18B20_ReadT();
	}
	
	if (isSet) {T0Count = 0; return;}	// 进入设置模式，则计数器回到初始状态
    T0Count++;
	
	// 最后3s每1s闪一次(一次暗亮)，黄灯除外
    if (T0Count == 10*100 || T0Count == 20*100) {
        // 南北方向闪烁处理
        if (SN.time <= BLINKTIME && SN.flag != YELLOW) {   
			SN.isBlink = !SN.isBlink;
			if (SN.time == 0) SN.isBlink = 0;	// 0s应该让Blink=0，防止后面不显示
			blink(&SN);
        }       
        // 东西方向闪烁处理
        if (EW.time <= BLINKTIME && EW.flag != YELLOW) {
			EW.isBlink = !EW.isBlink;
			if (EW.time == 0)	EW.isBlink = 0;	// 0s应该让Blink=0，防止后面不显示
			blink(&EW);
        }
    }
	
	// 每一秒
	if (T0Count == 20*100) {
		T0Count = 0;
		SN.time--;
		EW.time--;
	
		// 时间到了，南北换灯
        if (SN.time == 0) {
            if (SN.flag == GREEN) {
                setYellow(&SN);
            } else if (SN.flag == YELLOW) {
                setRed(&SN);
            } else if (SN.flag == RED) {
                setGreen(&SN);
            }
        }
		// 时间到了，东西换灯
        if (EW.time == 0) {
            if (EW.flag == GREEN) {
                setYellow(&EW);
            } else if (EW.flag == YELLOW) {
                setRed(&EW);
            } else if (EW.flag == RED) {
                setGreen(&EW);
            }
        }
	}
}
