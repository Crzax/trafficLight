/**************************************************
 * Author:       Crzax
 * Date:         2024-10-31
 * Description:  红外遥控器相关
 **************************************************/

#include <REGX52.H>
#include "Timer.h"
#include "Int0.h"
#include "IR.h"
#include "TrafficLight.h"
unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData;

unsigned char IR_DataFlag;  
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;

/**
  * @brief  遥控器初始化
  * @param  无
  * @retval 无
  */
void IR_Init(void)
{
	Timer1_Init();
	Int0_Init();
}

/**
  * @brief  获取data位，判断是否拿到了数据
  * @param  无
  * @retval dataFlag
  */
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief  红外遥控获取收到的命令数据
  * @param  无
  * @retval 收到的命令数据
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

/**
  * @brief  获取目前的Command所指的数字/指令
  * @param  无
  * @retval 当前Command对应的数字/指令，如果不是已经定义含义的数字/指令，那么返回INVALID
			同时返回后置IR_Command为0
  */
unsigned char IR_GetNumber(void)
{
	switch (IR_Command) {
		case IR_0: IR_Command = 0; return 0;break;
		case IR_1: IR_Command = 0; return 1;break;
		case IR_2: IR_Command = 0; return 2;break;
		case IR_3: IR_Command = 0; return 3;break;
		case IR_4: IR_Command = 0; return 4;break;
		case IR_5: IR_Command = 0; return 5;break;
		case IR_6: IR_Command = 0; return 6;break;
		case IR_7: IR_Command = 0; return 7;break;
		case IR_8: IR_Command = 0; return 8;break;
		case IR_9: IR_Command = 0; return 9;break;
		case IR_VOL_ADD: IR_Command = 0; return ADDONE;break;
		case IR_VOL_MINUS: IR_Command = 0; return SUBONE;break;
		case IR_MUTE: IR_Command = 0; return CLEAR;break;
		case IR_EQ: IR_Command = 0; return OK;break;
		default: IR_Command = 0;return INVALID;
	}
}

/**
  * @brief  外部中断0的处理函数，也是红外遥控器的解码函数，使用状态机的原理
  * @param  无
  * @retval 无
  */
void Int0_Routine(void) interrupt 0
{
	if (IR_State==0)
	{
		Timer1_SetCounter(0);
		Timer1_Run(1);
		IR_State = 1;
	}
	else if(IR_State==1)		//状态1，等待Start信号或Repeat信号
	{
		IR_Time=Timer1_GetCounter();	//获取上一次中断到此次中断的时间
		Timer1_SetCounter(0);	//定时计数器清0
		//如果计时为13.5ms，则接收到了Start信号（判定值在12MHz晶振下为13500，在11.0592MHz晶振下为12442）
		if(IR_Time>12442-500 && IR_Time<12442+500)
		{
			IR_State=2;			//置状态为2
		}
		//如果计时为11.25ms，则接收到了Repeat信号（判定值在12MHz晶振下为11250，在11.0592MHz晶振下为10368）
		else if(IR_Time>10368-500 && IR_Time<10368+500)
		{
			IR_RepeatFlag=1;	//置收到连发帧标志位为1
			Timer1_Run(0);		//定时器停止
			IR_State=0;			//置状态为0
		}
		else					//接收出错
		{
			IR_State=1;			//置状态为1
		}
	}
	else if(IR_State==2)		//状态2，接收数据
	{
		IR_Time=Timer1_GetCounter();	//获取上一次中断到此次中断的时间
		Timer1_SetCounter(0);	//定时计数器清0
		//如果计时为1120us，则接收到了数据0（判定值在12MHz晶振下为1120，在11.0592MHz晶振下为1032）
		if(IR_Time>1032-500 && IR_Time<1032+500)
		{
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));	//数据对应位清0
			IR_pData++;			//数据位置指针自增
		}
		//如果计时为2250us，则接收到了数据1（判定值在12MHz晶振下为2250，在11.0592MHz晶振下为2074）
		else if(IR_Time>2074-500 && IR_Time<2074+500)
		{
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//数据对应位置1
			IR_pData++;			//数据位置指针自增
		}
		else					//接收出错
		{
			IR_pData=0;			//数据位置指针清0
			IR_State=1;			//置状态为1
		}
		if(IR_pData>=32)		//如果接收到了32位数据
		{
			IR_pData=0;			//数据位置指针清0
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))	//数据验证
			{
				IR_Address=IR_Data[0];	//转存数据
				IR_Command=IR_Data[2];
				IR_DataFlag=1;	//置收到连发帧标志位为1
			}
			Timer1_Run(0);		//定时器停止
			IR_State=0;			//置状态为0
		}
	}
}

