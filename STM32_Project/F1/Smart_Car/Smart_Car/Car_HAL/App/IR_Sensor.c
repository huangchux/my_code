/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

static void Ir_Tracking(void);

/* Public variables-----------------------------------------------------------*/

IR_t IR =
    {
        .Ir_Tracking = Ir_Tracking,
};

/* function prototypes--------------------------------------------------------*/

/**
 * @name   Ir_Tracking
 * @param  None
 * @retval None
 * @brief  红外循迹
 */
static void Ir_Tracking(void)
{
    //   PID.Motor_Set_Speed(1,2); 	//左
    //   PID.Motor_Set_Speed(2,1); 	//右
    //   PID.Motor_Set_Speed(1,1); 	//前
    //   PID.Motor_Set_Speed(-1,-1); //后
    if (READ_HW_OUT_1 == 0 && READ_HW_OUT_2 == 0 && READ_HW_OUT_3 == 0 && READ_HW_OUT_4 == 0)
    {
        PID.Motor_Set_Speed(1, 1); // 前进
    }
    if (READ_HW_OUT_1 == 0 && READ_HW_OUT_2 == 1 && READ_HW_OUT_3 == 0 && READ_HW_OUT_4 == 0)
    {
        PID.Motor_Set_Speed(2, 0.5); // 右
    }
    if (READ_HW_OUT_1 == 1 && READ_HW_OUT_2 == 0 && READ_HW_OUT_3 == 0 && READ_HW_OUT_4 == 0)
    {
        PID.Motor_Set_Speed(2.5, 0.5); // 快右
    }
    if (READ_HW_OUT_1 == 0 && READ_HW_OUT_2 == 0 && READ_HW_OUT_3 == 1 && READ_HW_OUT_4 == 0)
    {
        PID.Motor_Set_Speed(0.5, 2); // 左
    }
    if (READ_HW_OUT_1 == 0 && READ_HW_OUT_2 == 0 && READ_HW_OUT_3 == 0 && READ_HW_OUT_4 == 1)
    {
        PID.Motor_Set_Speed(0.5, 2.5); // 快左
    }
}

/********************************************************
  End Of File
********************************************************/
