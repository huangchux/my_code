/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"


/* Private variables----------------------------------------------------------*/

static float HC_SR04_Read_Distance(void);
static float HC_SR04_Elude(void);
/* Public variables-----------------------------------------------------------*/

HC_SR04_t HC_SR04 =
{
    .HC_SR04_Read_Distance = HC_SR04_Read_Distance,
    .HC_SR04_Elude = HC_SR04_Elude,
};

/* function prototypes--------------------------------------------------------*/

/**
      * @name   HC_SR04_Read
      * @param  None
      * @retval 障碍物距离单位:cm (静止表面平整精度更高) 
      * @brief  HC_SR04读取超声波距离
      * 注意:两个HC_SR04_Read()函数调用的时间间隔要2ms及以上，测量范围更大 精度更高 
*/
/**
 * 测量距离，并返回距离值
 *
 * 这个函数使用HC-SR04超声波传感器模块进行测量，通过控制触发信号和回声信号来计算距离。
 * 首先将触发信号置高，持续一段时间后复位，然后等待回声信号出现并记录时间。
 * 通过计算时间和声速，可以得到物体与传感器之间的距离，并返回结果。
 * 如果测量失败，则返回-1或-2。
 */
static float HC_SR04_Read_Distance(void)
{
    uint32_t i = 0;
    float Distance;

    // 发送触发信号
    HAL_GPIO_WritePin(HC_SR04_Trig_GPIO_Port, HC_SR04_Trig_Pin, GPIO_PIN_SET);
    Public.Delay_us(15); // 延迟一段时间，至少10微秒
    HAL_GPIO_WritePin(HC_SR04_Trig_GPIO_Port, HC_SR04_Trig_Pin, GPIO_PIN_RESET);

    // 等待回声信号出现并记录时间
    while (HAL_GPIO_ReadPin(HC_SR04_Echo_GPIO_Port, HC_SR04_Echo_Pin) == GPIO_PIN_RESET)
    {
        i++;
        Public.Delay_us(1);
        if (i > 10000)
        {
            return -1; // 如果超时，则返回-1
        }
    }

    i = 0;
    while (HAL_GPIO_ReadPin(HC_SR04_Echo_GPIO_Port, HC_SR04_Echo_Pin) == GPIO_PIN_SET)
    {
        i = i + 1;
        Public.Delay_us(1);
        if (i > 10000)
        {
            return -2; // 如果超时，则返回-2
        }
    }

    // 计算距离并返回结果
    Distance = (i * 2 * 0.033 / 2) - 3; // 超声波传播速度为0.033cm/us
    return Distance;
}


/**
      * @name   HC_SR04_Elude
      * @param  None
      * @retval None
      * @brief  超声波避障
*/
static float HC_SR04_Elude(void)
{
    if(HC_SR04_Read_Distance() > 25)  // 如果超声波测得的距离大于25
    {
        PID.Motor_Set_Speed(1, 1);  // 设置电机速度，使小车前进
        HAL_Delay(100);  // 延时100毫秒
    }
    else  // 如果超声波测得的距离小于等于25
    {
        PID.Motor_Set_Speed(1, -1);  // 设置电机速度，使小车向右转

        HAL_Delay(500);  // 延时500毫秒

        if(HC_SR04_Read_Distance() > 25)  // 如果超声波测得的距离大于25
        {
            PID.Motor_Set_Speed(1, 1);  // 设置电机速度，使小车前进
            HAL_Delay(100);  // 延时100毫秒
        }
        else  // 如果超声波测得的距离仍然小于等于25
        {
            PID.Motor_Set_Speed(-1, 1);  // 设置电机速度，使小车向左转
            HAL_Delay(1000);  // 延时1000毫秒

            if(HC_SR04_Read_Distance() > 25)  // 如果超声波测得的距离大于25
            {
                PID.Motor_Set_Speed(1, 1);  // 设置电机速度，使小车前进
                HAL_Delay(100);  // 延时100毫秒
            }
            else  // 如果超声波测得的距离仍然小于等于25
            {
                PID.Motor_Set_Speed(-1, -1);  // 设置电机速度，使小车后退并向右转
                HAL_Delay(1000);  // 延时1000毫秒

                PID.Motor_Set_Speed(1, -1);  // 设置电机速度，使小车向右转
                HAL_Delay(200);  // 延时50毫秒
            }
        }
    }
}


/********************************************************
  End Of File
********************************************************/
