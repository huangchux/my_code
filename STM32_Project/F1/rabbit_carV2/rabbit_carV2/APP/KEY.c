/***************************************************************************
 * File: KEY.c
 * Author: Emily
 * Date: 2023/11/11
 * description: 按键
****************************************************************************/
#include "AllHead.h"

/* Private variables=========================================================*/
static uint8_t Key_value,Key_up,Key_down; // 按键键值 按键抬起 按键按下

/* Private function prototypes===============================================*/
static uint8_t KEY_Get_Value(void);
static void KEY_Scan(void);
static void KEY_Handler(void);


/* Public variables==========================================================*/
KEY_st KEY = 
{
    .Key_Long_Count = 0,
    .Key_Flag_Arr = {0},
    .KEY_Scan = &KEY_Scan,
    .KEY_Handler = &KEY_Handler,
};

/*
* @function: KEY_Get_Value
* @param: None
* @retval: None
* @brief: 返回键值
*/
static uint8_t KEY_Get_Value(void)
{
    uint8_t Key_Num = KEY_NULL;

    // KEY1 为下拉输入，所以KEY1为 1 时判断按键按下，KEY2 为上拉输入，所以KEY2为 0 时判断按键按下
    if(!KEY2) //判断按键是否按下 
    {
        if(!KEY2)
        {
            Key_Num = KEY2_DOWN; // 按键KEY2按下键值返回为2
        }
    }
    return Key_Num; // 返回键值
}

/*
* @function: KEY_Scan
* @param: None
* @retval: None
* @brief: 按键三行消抖---按键扫描
*/
static void KEY_Scan(void)
{
    static uint8_t Key_old;               // 上一次按键的键值
    static uint8_t Key_Long_Flag = FALSE; // 长按执行一次标志位

    Key_value = KEY_Get_Value();  // 读取按键的键值
    Key_up = ~Key_value & (Key_old ^ Key_value);   // 按键的上升沿检测 只在按键抬起的瞬间有效 其他时刻都为零无效
    Key_down = Key_value & (Key_old ^ Key_value);  // 按键的下降沿检测 只在按键按下的瞬间有效 其他时刻都为零无效
    Key_old = Key_value;   // 记录上一次按键按下后的键值
    
    if (Key_down)   // 当有按键按下时
    {
        KEY.Key_Long_Count = 0; // 将计时器清零 从零开始计时
        Key_Long_Flag = FALSE;  // 长按执行一次标志位清0
    }

    if (KEY.Key_Long_Count < 10)  // 如果计时时间小于1s 短按
    {
        switch (Key_up)           // 判断按键是否抬起 选择键值执行短按的相应程序
        {
        case KEY2_DOWN:
        {
            KEY.Key_Flag_Arr[0] = TRUE;
            break;
        }
        default:
            break;
        }
    }
    else   // 长按 计时时间超过1s
    {
        if (!Key_Long_Flag) // 第一次长按则进入if语句 按键按下不管长按短按的话Key_Long_Flag都会清0，取反后进入该语句
        {
            switch(Key_value)  //判断按键是否按下 选择按键的键值执行相应功能,如果这里改成key_up则按下松开才会执行下面
            {
                case KEY2_DOWN:
                {
                    KEY.Key_Flag_Arr[1] = TRUE;
                    break;
                }
                default:
                    break;
            }
            Key_Long_Flag = TRUE;  // 长按执行一次标志位置1
        }
    }

}

/*
* @function: KEY_Handler
* @param: None
* @retval: None
* @brief: 按键处理函数
*/
static void KEY_Handler(void)
{
    if(KEY.Key_Flag_Arr[0])  // KEY2按下
    {
		KEY.Key_Flag_Arr[0] = FALSE;
        Menu_Status = (Menu_Status - 1 + 1) % Page_MAX - 1 + 1 + 1; // 切换页面
        OLED.OLED_Clear();      
    }
    else if(KEY.Key_Flag_Arr[1]) // KEY2长按
    {
        KEY.Key_Flag_Arr[1] = FALSE;   
    }
}