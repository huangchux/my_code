/***************************************************************************
 * File: Relay.c
 * Author: Emily
 * Date: 2023/11/26
 * description: 继电器
 -----------------------------------
 继电器的接线：
 IN端接单片机的PB5
 DC+和常开端(NO)接电源的正极
 DC-分两路分别接电源的负极和单片机的负极
 COM端接灯带的正极，灯带的负极接电源的负极
 -----------------------------------
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Relay_Init(void);
static void Relay_Control(Relay_Number_et RelayX, Relay_State_et state);
static void Relay_Flip(Relay_Number_et RelayX);

/* Public variables==========================================================*/
Relay_st Relay = 
{
    .Relay_Status = {RELAY_OFF, RELAY_OFF, RELAY_OFF, RELAY_OFF},  
    .Relay_Flip_Count = 0,
    .Relay_Left_Count = 0,
    .Relay_Right_Count = 0,
    .Relay_Flip_Flag = FALSE,
    .Relay_Left_Flip_Flag = FALSE,
    .Relay_Right_Flip_Flag = FALSE,

    .Relay_Init = &Relay_Init,
    .Relay_Control = &Relay_Control,
    .Relay_Flip = &Relay_Flip,
};

/*
* @function: Relay_Init
* @param: None
* @retval: None
* @brief: 继电器初始化
*/
static void Relay_Init(void)
{
	__Relay_All_Close();
}

/*
* @function: Relay_Control
* @param: RelayX --> 选择哪个继电器   state --> 继电器状态位   RELAY_ON表示打开继电器 RELAY_OFF表示关闭继电器
* @retval: None
* @brief: 继电器控制
*/
static void Relay_Control(Relay_Number_et RelayX, Relay_State_et state)
{
    switch(RelayX) // 选择哪个继电器
    {
        case Relay_Body_White:    // 【身体白色灯继电器】
        {
            if (RELAY_ON == state) // 如果打开继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                     // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_White_GPIO_Port, Relay_White_Pin, GPIO_PIN_SET); // 高电平打开继电器
#else                                                                                    // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_White_GPIO_Port, Relay_White_Pin, GPIO_PIN_RESET); // 低电平打开继电器
#endif
                Relay.Relay_Status[Relay_Body_White] = RELAY_ON; // 白色灯继电器状态为打开
            }
            else // 如果关闭继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                       // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_White_GPIO_Port, Relay_White_Pin, GPIO_PIN_RESET); // 低电平关闭继电器
#else                                                                                      // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_White_GPIO_Port, Relay_White_Pin, GPIO_PIN_SET); // 高电平关闭继电器
#endif
                Relay.Relay_Status[Relay_Body_White] = RELAY_OFF; // 白色灯继电器状态为关闭
            }
            break; // 跳出循环
        }
        case Relay_Body_Yellow:   //  【身体黄色灯继电器】
        {
            if (RELAY_ON == state) // 如果打开继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                       // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_Yellow_GPIO_Port, Relay_Yellow_Pin, GPIO_PIN_SET); // 高电平打开继电器
#else                                                                                      // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_Yellow_GPIO_Port, Relay_Yellow_Pin, GPIO_PIN_RESET); // 低电平打开继电器
#endif
                Relay.Relay_Status[Relay_Body_Yellow] = RELAY_ON; // 黄色灯继电器状态为打开
            }
            else // 如果关闭继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                         // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_Yellow_GPIO_Port, Relay_Yellow_Pin, GPIO_PIN_RESET); // 低电平关闭继电器
#else                                                                                        // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_Yellow_GPIO_Port, Relay_Yellow_Pin, GPIO_PIN_SET); // 高电平关闭继电器
#endif
                Relay.Relay_Status[Relay_Body_Yellow] = RELAY_OFF; // 黄色灯继电器状态为关闭
            }
            break;
        }
        case Relay_Left:  //  【左耳朵继电器】
        {
            if (RELAY_ON == state) // 如果打开继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                   // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_Left_GPIO_Port, Relay_Left_Pin, GPIO_PIN_SET); // 高电平打开继电器
#else                                                                                  // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_Left_GPIO_Port, Relay_Left_Pin, GPIO_PIN_RESET); // 低电平打开继电器
#endif
                Relay.Relay_Status[Relay_Left] = RELAY_ON; // 左耳朵继电器状态为打开
            }
            else // 如果关闭继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                     // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_Left_GPIO_Port, Relay_Left_Pin, GPIO_PIN_RESET); // 低电平关闭继电器
#else                                                                                    // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_Left_GPIO_Port, Relay_Left_Pin, GPIO_PIN_SET); // 高电平关闭继电器
#endif
                Relay.Relay_Status[Relay_Left] = RELAY_OFF; // 左耳朵继电器状态为关闭
            }
            break;
        }
        case Relay_Right: //  【右耳朵继电器】
        {
            if (RELAY_ON == state) // 如果打开继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                     // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_Right_GPIO_Port, Relay_Right_Pin, GPIO_PIN_SET); // 高电平打开继电器
#else                                                                                    // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_Right_GPIO_Port, Relay_Right_Pin, GPIO_PIN_RESET); // 低电平打开继电器
#endif
                Relay.Relay_Status[Relay_Right] = RELAY_ON; // 右耳朵继电器状态为打开
            }
            else // 如果关闭继电器
            {
#ifdef USE_Relay_Trigger_Level_Hight                                                       // 如果是高电平触发继电器
                HAL_GPIO_WritePin(Relay_Right_GPIO_Port, Relay_Right_Pin, GPIO_PIN_RESET); // 低电平关闭继电器
#else                                                                                      // 如果是低电平触发继电器
                HAL_GPIO_WritePin(Relay_Right_GPIO_Port, Relay_Right_Pin, GPIO_PIN_SET); // 高电平关闭继电器
#endif
                Relay.Relay_Status[Relay_Right] = RELAY_OFF; // 右耳朵继电器状态为关闭
            }
            break;
        }
        default:break;
    }
}

/*
* @function: Relay_Flip
* @param: RelayX --> 选择哪个继电器
* @retval: None
* @brief: 翻转继电器
*/
static void Relay_Flip(Relay_Number_et RelayX)
{
    switch (RelayX) // 选择哪个继电器
    {
        case Relay_Left: // 【左耳朵继电器】
        {
            if (RELAY_ON == Relay.Relay_Status[Relay_Left]) // 如果左耳朵继电器状态为打开
            {
                Relay_Control(Relay_Left, RELAY_OFF); // 关闭左耳朵继电器
            }
            else // 如果左耳朵继电器状态为关闭
            {
                Relay_Control(Relay_Left, RELAY_ON);  // 打开左耳朵继电器
            }
            break;
        }
        case Relay_Right:  // 【右耳朵继电器】
        {
            
            if (RELAY_ON == Relay.Relay_Status[Relay_Right]) // 如果右耳朵继电器状态为打开
            {
                Relay_Control(Relay_Right, RELAY_OFF); // 关闭右耳朵继电器
            }
            else // 如果右耳朵继电器状态为关闭
            {
                Relay_Control(Relay_Right, RELAY_ON); // 打开右耳朵继电器
            }            
            break;
        }
        case Relay_Body_White: // 【白色灯继电器】
        {
            if (RELAY_ON == Relay.Relay_Status[Relay_Body_White]) // 如果白色灯继电器状态为打开
            {
                Relay_Control(Relay_Body_White, RELAY_OFF); // 关闭白色灯继电器
            }
            else  // 如果白色灯继电器状态为关闭
            {
                Relay_Control(Relay_Body_White, RELAY_ON); // 打开白色灯继电器
            }            
            break;
        }
        case Relay_Body_Yellow: // 【黄色灯继电器】
        {
            if (RELAY_ON == Relay.Relay_Status[Relay_Body_Yellow]) // 如果黄色灯继电器状态为打开
            {
                Relay_Control(Relay_Body_Yellow, RELAY_OFF); // 关闭黄色灯继电器
            }
            else
            {
                Relay_Control(Relay_Body_Yellow, RELAY_ON);  // 打开黄色灯继电器
            }            
            break;
        }
        default:break;
    }
}