#ifndef __INFRARED_H
#define __INFRARED_H

// 宏定义红外对管连接的GPIO电平
#define Read_HW_OUT_1   HAL_GPIO_ReadPin(HW_OUT_1_GPIO_Port,HW_OUT_1_Pin)
#define Read_HW_OUT_2   HAL_GPIO_ReadPin(HW_OUT_2_GPIO_Port,HW_OUT_2_Pin)
#define Read_HW_OUT_3   HAL_GPIO_ReadPin(HW_OUT_3_GPIO_Port,HW_OUT_3_Pin)
#define Read_HW_OUT_4   HAL_GPIO_ReadPin(HW_OUT_4_GPIO_Port,HW_OUT_4_Pin)

typedef struct
{
    uint8_t HW_Read_OUT[4];                // 保存红外对管电平的数组
    void (*PID_Control_HW_Tracking)(void); // PID控制红外寻迹
} Infrared_st;

extern Infrared_st Infrared;

#endif
