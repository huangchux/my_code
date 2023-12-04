#ifndef __PID_H
#define __PID_H

#define READ_HW_OUT_1 HAL_GPIO_ReadPin(HW_OUT_1_GPIO_Port, HW_OUT_1_Pin)
#define READ_HW_OUT_2 HAL_GPIO_ReadPin(HW_OUT_2_GPIO_Port, HW_OUT_2_Pin)
#define READ_HW_OUT_3 HAL_GPIO_ReadPin(HW_OUT_3_GPIO_Port, HW_OUT_3_Pin)
#define READ_HW_OUT_4 HAL_GPIO_ReadPin(HW_OUT_4_GPIO_Port, HW_OUT_4_Pin)

// 结构体类型
typedef struct
{
	float target_val; // 目标值
	float actual_val; // 实际值
	float err;		  // 当前偏差
	float err_last;	  // 上次偏差
	float err_sum;	  // 误差累计值
	float KP, KI, KD; // 比例，积分，微分系数
} PID_Motor_Speed_t;

typedef struct
{
	void (*PID_Init)(void);											// PID初始化
	float (*P_realize)(PID_Motor_Speed_t *pid, float actual_val);	// P控制算法
	float (*PI_realize)(PID_Motor_Speed_t *pid, float actual_val);	// PI控制算法
	float (*PID_realize)(PID_Motor_Speed_t *pid, float actual_val); // PID控制算法
	void (*Motor_Set_Speed)(float, float);							// PID控制电机速度
	void (*PID_Ir_Tracking)(void);
} PID_t;

/* extern variables-----------------------------------------------------------*/

extern PID_t PID;
extern PID_Motor_Speed_t PID_Motor1_Speed;
extern PID_Motor_Speed_t PID_Motor2_Speed;
extern PID_Motor_Speed_t PID_HW_Tracking;
extern PID_Motor_Speed_t PID_HC_SR04_Follow;
extern  void HC_SR04_Follow(void);

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
