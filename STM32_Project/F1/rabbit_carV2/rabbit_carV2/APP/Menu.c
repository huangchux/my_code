/***************************************************************************
 * File: Menu.c
 * Author: Emily
 * Date: 2023/11/13
 * description: 显示界面
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Menu_Init(void);
static void Menu_Handler(void);

static void Menu_Display_1(void);
static void Menu_Display_2(void);
static void Menu_Display_3(void);
static void Menu_Display_4(void);
static void Menu_Display_5(void);
static void Menu_Display_6(void);
/* Public variables==========================================================*/
Menu_Status_et Menu_Status;
Menu_st Menu = 
{
    .Menu_Init = &Menu_Init,
    .Menu_Handler = &Menu_Handler
};

/*
* @function: Menu_Init
* @param: None
* @retval: None
* @brief: 页面初始化
*/
static void Menu_Init(void)
{
    Menu_Status = Page_Power;   // 上电默认显示电量页面
}

/*
* @function: Menu_Handler
* @param: None
* @retval: None
* @brief: 页面切换显示
*/
static void Menu_Handler(void)
{
    switch(Menu_Status)  // 选择页面
    {
        case Page_Power:  // 电量显示页面
        {
            Menu_Display_1(); 
            break;
        }
        case Page_Encoder: // 显示编码器数据
        {
            Menu_Display_2(); 
            break;
        }
        case Page_Track_Light: // 显示寻迹灯的电平状态
        {
            Menu_Display_3(); 
            break;
        } 
        case Page_Left_Motor_PID: // 显示左电机的PID参数
        {
            Menu_Display_4(); 
            break;
        }  
        case Page_Right_Motor_PID: // 显示右电机的PID参数
        {
            Menu_Display_5(); 
            break;
        }      
        case Page_Track_PID: // 显示寻迹的PID参数
        {
            Menu_Display_6(); 
            break;
        }                       
        default:
            break;
    }
}

/*
* @function: Menu_Display_1
* @param: None
* @retval: None
* @brief: 页面1  电量显示页面
*/
static void Menu_Display_1(void)
{
  uint8_t arr[20] = "\0";

  OLED.OLED_Show_String(0, OLED096_Line1, "     Power  ", ASCII_SIZE_16);

  bsp_ADC.Bsp_ADC_Get_Battery_Voltage(); // 计算电压

  sprintf((char *)arr, "ADC:%.1f V", bsp_ADC.Battery_Voltage);
  OLED.OLED_Fill_Space(arr);
  OLED.OLED_Show_String(0, OLED096_Line2, (char *)arr, ASCII_SIZE_16);

  memset(arr, 0, strlen((char *)arr)); // 使用memset函数将arr清零，即将所有字符赋值为0
}

/*
* @function: Menu_Display_2
* @param: None
* @retval: None
* @brief: 页面2  显示编码器数据
*/
static void Menu_Display_2(void)
{
    uint8_t arr[20] = "\0";

    OLED.OLED_Show_String(0, OLED096_Line1,"    Encoder  ", ASCII_SIZE_16);  // 第一行

    sprintf((char*)arr, "Mileage:%.0f CM", Encoder.Mileage);
		OLED.OLED_Fill_Space(arr);                                               // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line2, (char*)arr, ASCII_SIZE_16);      // 第二行显示里程数

    memset(arr, 0, strlen((char *)arr)); // 使用memset函数将arr清零，即将所有字符赋值为0
    sprintf((char *)arr, "L_Speed:%.1f", Encoder.Encoder_Left_Speed);
    OLED.OLED_Fill_Space(arr);
    OLED.OLED_Show_String(0, OLED096_Line3, (char *)arr, ASCII_SIZE_16); // 第三行显示左电机的速度

    memset(arr, 0, strlen((char*)arr));
    sprintf((char*)arr, "R_Speed:%.1f", Encoder.Encoder_Right_Speed);
		OLED.OLED_Fill_Space(arr);
    OLED.OLED_Show_String(0, OLED096_Line4, (char*)arr, ASCII_SIZE_16);      // 第四行显示右电机的速度    
}

/*
* @function: Menu_Display_3
* @param: None
* @retval: None
* @brief: 页面3  显示寻迹灯的电平状态
*/
static void Menu_Display_3(void)
{
    uint8_t arr[20] = "\0";

    OLED.OLED_Show_String(0, OLED096_Line1,"  Track Light  ", ASCII_SIZE_16);  // 第一行
    OLED.OLED_Show_String(0, OLED096_Line2,"  L-----R  ", ASCII_SIZE_16);      // 第二行

		memset(arr, 0, strlen((char*)arr));     // 使用memset函数将arr清零，即将所有字符赋值为0
    sprintf((char*)arr, "%d  %d  %d  %d",Infrared.HW_Read_OUT[0],Infrared.HW_Read_OUT[1],Infrared.HW_Read_OUT[2],Infrared.HW_Read_OUT[3]);
		OLED.OLED_Fill_Space(arr); // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line3, (char*)arr, ASCII_SIZE_16);      // 第三行显示寻迹灯的电平状态    
}

/*
* @function: Menu_Display_4
* @param: None
* @retval: None
* @brief: 页面4  显示左电机的PID参数
*/
static void Menu_Display_4(void)
{
    uint8_t arr[20] = "\0";

    OLED.OLED_Show_String(0, OLED096_Line1,"  Left PID  ", ASCII_SIZE_16);  // 第一行

    sprintf((char *)arr, "tar:%.1fact:%.1f", PID_Motor_Left.target_val, PID_Motor_Left.actual_val);
    OLED.OLED_Fill_Space(arr);                                           // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line2, (char *)arr, ASCII_SIZE_16); 
    memset(arr, 0, strlen((char *)arr));                                 // 使用memset函数将arr清零，即将所有字符赋值为0

    sprintf((char *)arr, "P:%.1fI:%.1fD:%.1f", PID_Motor_Left.Kp, PID_Motor_Left.Ki, PID_Motor_Left.Kd);
    OLED.OLED_Fill_Space(arr);                                           // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line3, (char *)arr, ASCII_SIZE_16);               
}

/*
* @function: Menu_Display_5
* @param: None
* @retval: None
* @brief: 页面5  显示右电机的PID参数
*/
static void Menu_Display_5(void)
{
    uint8_t arr[20] = "\0";

    OLED.OLED_Show_String(0, OLED096_Line1,"  Right PID  ", ASCII_SIZE_16);  // 第一行

    sprintf((char*)arr, "tar:%.1fact:%.1f", PID_Motor_Right.target_val, PID_Motor_Right.actual_val);
		OLED.OLED_Fill_Space(arr);
    OLED.OLED_Show_String(0, OLED096_Line2, (char*)arr, ASCII_SIZE_16);     
    memset(arr, 0, strlen((char*)arr)); 

    sprintf((char*)arr, "P%.1fI%.1fD%.1f", PID_Motor_Right.Kp, PID_Motor_Right.Ki, PID_Motor_Right.Kd);
		OLED.OLED_Fill_Space(arr);
    OLED.OLED_Show_String(0, OLED096_Line3, (char*)arr, ASCII_SIZE_16);               
}

/*
* @function: Menu_Display_6
* @param: None
* @retval: None
* @brief: 页面6  显示寻迹的PID参数
*/
static void Menu_Display_6(void)
{
    uint8_t arr[20] = "\0";

    OLED.OLED_Show_String(0, OLED096_Line1, "  Track PID  ", ASCII_SIZE_16); // 第一行

    sprintf((char *)arr, "P:  %.2f", PID_HW_Tracking.Kp); // 红外寻迹比例系数
    OLED.OLED_Fill_Space(arr);                            // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line2, (char *)arr, ASCII_SIZE_16);
    memset(arr, 0, strlen((char *)arr)); // 使用memset函数将arr清零，即将所有字符赋值为0

    sprintf((char *)arr, "I:  %.2f", PID_HW_Tracking.Ki); // 红外寻迹积分系数
    OLED.OLED_Fill_Space(arr);                            // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line3, (char *)arr, ASCII_SIZE_16);
    memset(arr, 0, strlen((char *)arr)); // 使用memset函数将arr清零，即将所有字符赋值为0

    sprintf((char *)arr, "D:  %.2f", PID_HW_Tracking.Kd); // 红外寻迹微分系数
    OLED.OLED_Fill_Space(arr);                            // 补全空格
    OLED.OLED_Show_String(0, OLED096_Line4, (char *)arr, ASCII_SIZE_16);
}