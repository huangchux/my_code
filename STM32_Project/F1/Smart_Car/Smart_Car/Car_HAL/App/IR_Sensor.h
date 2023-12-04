#ifndef __IR_SENSOR_H
#define __IR_SENSOR_H

//#define READ_HW_OUT_1 HAL_GPIO_ReadPin(HW_OUT_1_GPIO_Port,HW_OUT_1_Pin)
//#define READ_HW_OUT_2 HAL_GPIO_ReadPin(HW_OUT_2_GPIO_Port,HW_OUT_2_Pin)
//#define READ_HW_OUT_3 HAL_GPIO_ReadPin(HW_OUT_3_GPIO_Port,HW_OUT_3_Pin)
//#define READ_HW_OUT_4 HAL_GPIO_ReadPin(HW_OUT_4_GPIO_Port,HW_OUT_4_Pin)

typedef struct 
{
    void (*Ir_Tracking)(void);
} IR_t;

/* extern variables-----------------------------------------------------------*/

extern IR_t IR;

/* extern function prototypes-------------------------------------------------*/


#endif
/********************************************************
  End Of File
********************************************************/
