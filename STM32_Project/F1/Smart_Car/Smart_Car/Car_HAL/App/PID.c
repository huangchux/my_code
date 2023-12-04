/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

static void PID_Init(void);
static float P_realize(PID_Motor_Speed_t *pid, float actual_val);
static float PI_realize(PID_Motor_Speed_t *pid, float actual_val);
static float PID_realize(PID_Motor_Speed_t *pid, float actual_val);
static void Motor_Set_Speed(float, float);
static void PID_Ir_Tracking(void);

void PID_Motor1_Speed_Init(void);
void PID_Motor2_Speed_Init(void);
void PID_Ir_Tracking_Init(void);
void PID_HC_SR04_Follow_Init(void);

uint8_t HW_Read[4] = {0};
int8_t ThisState = 0, LastState = 0;
float HW_PID_Out, HW_PID_Out1, HW_PID_Out2, HC_SR04_Read, PID_Follow_Out;

/* Public variables-----------------------------------------------------------*/

// 初始化PID控制器对象
PID_t PID =
    {
        .PID_Init = PID_Init,               // PID初始化
        .P_realize = P_realize,             // P控制算法
        .PI_realize = PI_realize,           // PI控制算法
        .PID_realize = PID_realize,         // PID控制算法
        .Motor_Set_Speed = Motor_Set_Speed, // 控制电机速度
        .PID_Ir_Tracking = PID_Ir_Tracking,
};

// 初始化电机1的PID控制器的速度参数结构体
PID_Motor_Speed_t PID_Motor1_Speed;
// 初始化电机2的PID控制器的速度参数结构体
PID_Motor_Speed_t PID_Motor2_Speed;
// 初始化红外的PID控制器的速度参数结构体
PID_Motor_Speed_t PID_HW_Tracking;
// 初始化超声波的PID控制器的速度参数结构体
PID_Motor_Speed_t PID_HC_SR04_Follow;

/* function prototypes--------------------------------------------------------*/

/*
 * @name   PID_Init
 * @param  None
 * @retval None
 * @brief  初始化PID
 */
static void PID_Init(void)
{
  // 电机速度PID控制器的初始化
  PID_Motor1_Speed_Init();
  PID_Motor2_Speed_Init();
  PID_Ir_Tracking_Init();
  PID_HC_SR04_Follow_Init();
}

/**
 * @name   P_realize
 * @param  ctual_val 当前的真实值
 * @retval 计算后的控制量
 * @brief  P控制算法
 */
static float P_realize(PID_Motor_Speed_t *pid, float actual_val)
{
  pid->actual_val = actual_val;                 // 传递真实值
  pid->err = pid->target_val - pid->actual_val; // 当前误差 = 目标值 - 真实值

  // 比例控制调节，输出 = Kp * 当前误差
  pid->actual_val = pid->KP * pid->err;

  return pid->actual_val; // 返回计算后的控制量
}

/**
 * @name   PI控制算法
 * @param  actual_val 当前的真实值
 * @retval 计算后的控制量
 * @brief  PI控制算法
 */
static float PI_realize(PID_Motor_Speed_t *pid, float actual_val)
{
  pid->actual_val = actual_val;                 // 传递真实值
  pid->err = pid->target_val - pid->actual_val; // 当前误差 = 目标值 - 真实值
  pid->err_sum += pid->err;                     // 累计误差和，用于积分项

  // PI控制调节，输出 = KP * 当前误差 + KI * 累计误差和
  pid->actual_val = pid->KP * pid->err + pid->KI * pid->err_sum;

  return pid->actual_val; // 返回计算后的控制量
}

/**
 * @name   PID_realize
 * @param  actual_val 当前的真实值
 * @retval 计算后的控制量
 * @brief  PID控制算法
 */
static float PID_realize(PID_Motor_Speed_t *pid, float actual_val)
{
  pid->actual_val = actual_val;                 // 传递真实值
  pid->err = pid->target_val - pid->actual_val; // 当前误差 = 目标值 - 真实值
  pid->err_sum += pid->err;                     // 累计误差和，用于积分项

  // PID控制调节，输出 = KP * 当前误差 + KI * 累计误差和 + KD * (当前误差 + 前一次误差)
  pid->actual_val = pid->KP * pid->err + pid->KI * pid->err_sum + pid->KD * (pid->err + pid->err_last);

  pid->err_last = pid->err; // 保存当前误差到前一次误差中

  return pid->actual_val; // 返回计算后的控制量
}

/**
 * @name   Motor_Set_Speed
 * @param  None
 * @retval None
 * @brief  通过PID设置电机速度与方向
  PID.Motor_Set_Speed(1,2); 	//左
  PID.Motor_Set_Speed(2,1); 	//右
  PID.Motor_Set_Speed(1,1); 	//前
  PID.Motor_Set_Speed(-1,-1); //后
  PID.Motor_Set_Speed(0,0); 	//停
  PID.Motor_Set_Speed(-1,1);  //原地左旋转
  PID.Motor_Set_Speed(1,-1);  //原地右旋转m
 */
static void Motor_Set_Speed(float Motor1_SetSpeed, float Motor2_SetSpeed)
{
  // 改变电机PID参数的目标速度
  PID_Motor1_Speed.target_val = Motor1_SetSpeed;
  PID_Motor2_Speed.target_val = Motor2_SetSpeed;

  Motor.Motor_set(PID.PID_realize(&PID_Motor1_Speed, Motor1Speed), PID.PID_realize(&PID_Motor2_Speed, Motor2Speed));
}

/**
 * @name   PID_Ir_Tracking
 * @param  None
 * @retval None
 * @brief  PID控制红外循迹
 */
static void PID_Ir_Tracking(void)
{

  HW_Read[0] = READ_HW_OUT_1;
  HW_Read[1] = READ_HW_OUT_2;
  HW_Read[2] = READ_HW_OUT_3;
  HW_Read[3] = READ_HW_OUT_4;

  if (HW_Read[0] == 0 && HW_Read[1] == 0 && HW_Read[2] == 0 && HW_Read[3] == 0)
  {
    ThisState = 0;
  }

  else if (HW_Read[0] == 0 && HW_Read[1] == 1 && HW_Read[2] == 0 && HW_Read[3] == 0)
  {
    ThisState = -1;
  }

  else if (HW_Read[0] == 1 && HW_Read[1] == 0 && HW_Read[2] == 0 && HW_Read[3] == 0)
  {
    ThisState = -2;
  }

  else if (HW_Read[0] == 1 && HW_Read[1] == 1 && HW_Read[2] == 0 && HW_Read[3] == 0)
  {
    ThisState = -3;
  }

  else if (HW_Read[0] == 0 && HW_Read[1] == 0 && HW_Read[2] == 1 && HW_Read[3] == 0)
  {
    ThisState = 1;
  }

  else if (HW_Read[0] == 0 && HW_Read[1] == 0 && HW_Read[2] == 0 && HW_Read[3] == 1)
  {
    ThisState = 2;
  }

  else if (HW_Read[0] == 0 && HW_Read[1] == 0 && HW_Read[2] == 1 && HW_Read[3] == 1)
  {
    ThisState = 3;
  }
  HW_PID_Out = PID.PID_realize(&PID_HW_Tracking, ThisState);
  HW_PID_Out1 = 3 + HW_PID_Out;
  HW_PID_Out2 = 3 - HW_PID_Out;
  if (HW_PID_Out1 > 5)
  {
    HW_PID_Out1 = 5;
  }
  if (HW_PID_Out1 < 0)
  {
    HW_PID_Out1 = 0;
  }
  if (HW_PID_Out2 > 5)
  {
    HW_PID_Out2 = 5;
  }
  if (HW_PID_Out2 < 0)
  {
    HW_PID_Out2 = 0;
  }
  if (ThisState != LastState)
  {
    PID.Motor_Set_Speed(HW_PID_Out1, HW_PID_Out2);
  }

  LastState = ThisState;
}

/**
 * @name  HC_SR04_Follow
 * @param  None
 * @retval None
 * @brief	PID超声波跟随
 */
void HC_SR04_Follow(void)
{
  HC_SR04_Read = HC_SR04.HC_SR04_Read_Distance();
  if (HC_SR04_Read < 60)
  {
    PID_Follow_Out = PID.PID_realize(&PID_HC_SR04_Follow, HC_SR04_Read);
    if (PID_Follow_Out > 6)
    {
      PID_Follow_Out = 6;
    }
    if (PID_Follow_Out < -6)
    {
      PID_Follow_Out = -6;
    }
    PID.Motor_Set_Speed(-PID_Follow_Out, -PID_Follow_Out);
  }
  else
  {
    PID.Motor_Set_Speed(0, 0); // 如果前面60cm 没有东西就停止
  }
  HAL_Delay(10); // 读取超声波传感器不能过快
}

/**
 * @name   PID_Motor1_Speed_Init
 * @param  None
 * @retval None
 * @brief  电机1PID初始化
 */
void PID_Motor1_Speed_Init(void)
{
  PID_Motor1_Speed.actual_val = 0.0; // 实际值
  PID_Motor1_Speed.target_val = 0.0; // 目标值
  PID_Motor1_Speed.err = 0.0;        // 当前偏差
  PID_Motor1_Speed.err_last = 0.0;   // 上次偏差
  PID_Motor1_Speed.err_sum = 0.0;    // 误差累计值
  PID_Motor1_Speed.KP = 15;          // 比例系数
  PID_Motor1_Speed.KI = 5;           // 积分系数
  PID_Motor1_Speed.KD = 0;           // 微分系数
}

/**
 * @name   PID_Motor2_Speed_Init
 * @param  None
 * @retval None
 * @brief  电机2PID初始化
 */
void PID_Motor2_Speed_Init(void)
{
  PID_Motor2_Speed.actual_val = 0.0; // 实际值
  PID_Motor2_Speed.target_val = 0.0; // 目标值
  PID_Motor2_Speed.err = 0.0;        // 当前偏差
  PID_Motor2_Speed.err_last = 0.0;   // 上次偏差
  PID_Motor2_Speed.err_sum = 0.0;    // 误差累计值
  PID_Motor2_Speed.KP = 15;          // 比例系数
  PID_Motor2_Speed.KI = 5;           // 积分系数
  PID_Motor2_Speed.KD = 0;           // 微分系数
}

/**
 * @name
 * @param  None
 * @retval None
 * @brief
 */
void PID_Ir_Tracking_Init(void)
{
  PID_HW_Tracking.actual_val = 0.0;
  PID_HW_Tracking.target_val = 0.0;
  PID_HW_Tracking.err = 0.0;
  PID_HW_Tracking.err_last = 0.0;
  PID_HW_Tracking.err_sum = 0.0;
  PID_HW_Tracking.KP = -1;
  PID_HW_Tracking.KI = 0.0;
  PID_HW_Tracking.KD = 0.80;
}

void PID_HC_SR04_Follow_Init()
{
  PID_HC_SR04_Follow.actual_val = 0;
  PID_HC_SR04_Follow.target_val = 22.5;
  PID_HC_SR04_Follow.err = 0;
  PID_HC_SR04_Follow.err_last = 0;
  PID_HC_SR04_Follow.err_sum = 0;
  PID_HC_SR04_Follow.KP = 0.5;
  PID_HC_SR04_Follow.KI = -0.001;
  PID_HC_SR04_Follow.KD = 0;
}

/********************************************************
  End Of File
********************************************************/
