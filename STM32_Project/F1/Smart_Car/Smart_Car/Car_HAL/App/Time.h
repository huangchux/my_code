#ifndef __TIME_H
#define __TIME_H

// 枚举类型
typedef enum
{
	TIMER3_10ms = (uint16_t)2,
	TIMER3_50ms = (uint16_t)10,
	TIMER3_100ms = (uint16_t)20,
	TIMER3_200ms = (uint16_t)40,
	TIMER3_500ms = (uint16_t)100,
	TIMER3_1S = (uint16_t)200,
	TIMER3_2S = (uint16_t)400,
	TIMER3_3S = (uint16_t)600,
	TIMER3_5S = (uint16_t)1000,
	TIMER3_10S = (uint16_t)2000,
	TIMER3_30S = (uint16_t)6000,
	TIMER3_1min = (uint16_t)12000,
	TIMER3_3min = (uint16_t)36000,
} TIMER3_Value_t;

// 结构体类型
typedef struct
{
	uint16_t volatile usMCU_Run_Timer; // 系统运行定时器
	void (*Time_Init)(void);		   // 定时器初始化
} Timer_T;

/* extern variables-----------------------------------------------------------*/

extern Timer_T Timer;

extern short Encode1Count, Encode2Count; // 编码器脉冲计数
extern float Motor1Speed, Motor2Speed,Mileage;	 // 电机速度
extern uint16_t TimerCount;				 // 定时器计数
extern int Motor1Pwm, Motor2Pwm;		 // 电机的PWM值

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
