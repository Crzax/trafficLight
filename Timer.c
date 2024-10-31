/**************************************************
 * Author:       陈震雄
 * Date:         2024-10-29
 * Description:  与定时器有关
 **************************************************/


#include <REGX52.H>

/**
  * @brief  上电初始化，启动定时器0
  * @param  无
  * @retval 无
  */
void Timer0Init(void)		//500微秒@11.0592MHz
{
	TMOD &= 0xF0;    // 清零定时器0的模式位
    TMOD |= 0x01;    // 设置定时器0为模式1（16位定时器）
    TL0 = 0x33;      // 设置定时器0低字节初值
    TH0 = 0xFE;      // 设置定时器0高字节初值
    TF0 = 0;         // 清除定时器0的溢出标志位
    TR0 = 1;         // 启动定时器0
    ET0 = 1;         // 使能定时器0中断
    EA = 1;          // 使能总中断
}

/**
  * @brief  上电初始化，启动定时器1
  * @param  无
  * @retval 无
  */
void Timer1_Init(void)		//500微秒@11.0592MHz
{
	TMOD &= 0x0F;		//设置定时器1模式
	TMOD |= 0x10;		//设置定时器1模式
	TL1 = 0;		//设置定时初值
	TH1 = 0;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 0;		//定时器1开始计时
	ET1 = 1;         // 使能定时器0中断
    EA = 1;          // 使能总中断
}

/**
  * @brief  设置计时器1的起始值
  * @param  无
  * @retval 无
  */
void Timer1_SetCounter(unsigned int Value)
{
	TH1 = Value/256;
	TL1 = Value%256;
}

/**
  * @brief  获得计时器1的计时
  * @param  无
  * @retval 计时器1的计时结果
  */
unsigned int Timer1_GetCounter(void)
{
	return (TH1<<8)|TL1;
}

/**
  * @brief  启动/关闭计时器1
  * @param  unsigned char，1表示启动，0表示关闭
  * @retval 无
  */
void Timer1_Run(unsigned char Flag) {
	TR1 = Flag;
}
/**
  * @brief  计时器中断处理函数模板
  * @param  无
  * @retval 无
  */
//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count;
//	TL0 = 0x00;		//设置定时初值
//	TH0 = 0x4C;		//设置定时初值
//	T0Count++;
//	if (T0Count>=1000)
//	{
//		T0Count=0;
//	}
//}

/**
  * @brief  计时器2初始化
  * @param  无
  * @retval 无
  */
void Timer2_Init(void)
{
	T2CON = 0;
	TL2 = 0;
	TH2 = 0;
	RCAP2L = 0;
	RCAP2H = 0;
	TR2 = 0;
	TF2 = 0;
}

/**
  * @brief  设置计时器2的起始值
  * @param  无
  * @retval 无
  */
void Timer2_SetCounter(unsigned int Value)
{
	TH2 = Value/256;
	TL2 = Value%256;
	RCAP2H= Value/256;
	RCAP2L= Value%256;
}

/**
  * @brief  获得计时器2的计时
  * @param  无
  * @retval 计时器2的计时结果
  */
unsigned int Timer2_GetCounter(void)
{
	return (TH2<<8)|TL2;
}

/**
  * @brief  启动/关闭计时器2
  * @param  unsigned char，1表示启动，0表示关闭
  * @retval 无
  */
void Timer2_Run(unsigned char Flag) {
	TR2 = Flag;
}