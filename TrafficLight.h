/**************************************************
 * Author:       陈震雄
 * Date:         2024-10-30
 * Description:  交通灯的一些常量与全局变量
 **************************************************/


#ifndef __TRAFFICLIGHT_H__
#define __TRAFFICLIGHT_H__

#define GREEN 1			// 绿灯
#define RED 2			// 红灯
#define YELLOW 3		// 黄灯
#define GREENTIME 13 	// 绿灯时间
#define REDTIME 16		// 红灯时间
#define YELLOWTIME 3	// 黄灯时间
#define BLINKTIME 3     // 进入闪烁的时间
#define BUZZERTIME 6	// 进入叫的时间
#define ADDONE 11			// 倒计时加1
#define SUBONE 12			// 倒计时加1
#define CLEAR 13			// 倒计时清零
#define OK 14					// 倒计时确认
#define INVALID 15		// 不合法的控制信号，这样
#define TH  28				// 温度阈值
#endif