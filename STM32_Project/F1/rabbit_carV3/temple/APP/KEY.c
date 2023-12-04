/***************************************************************************
 * File: KEY.c
 * Author: Emily
 * Date: 2023/11/20
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Private variables=========================================================*/
static uint8_t Key_value,Key_up,Key_down;  // 按键键值 按键抬起 按键按下

/* Private function prototypes===============================================*/
static uint8_t Key_Get_Value(void);
static void Key_Scan(void);
static void KEY_Handler(void);

/* Public variables==========================================================*/
KEY_st KEY = 
{
    .Key_Long_Count = 0,
    .Key_Flag_Arr = {0},
    .Key_Scan = &Key_Scan,
    .KEY_Handler = &KEY_Handler
};

/*
* @function: Key_Get_Value
* @param: None
* @retval: None
* @brief: 获取按键键值
*/
static uint8_t Key_Get_Value(void)
{
    uint8_t Key_Num = KEY_NULL;

    // KEY1 为下拉输入，所以KEY1为 1 时判断按键按下，KEY2 为上拉输入，所以KEY2为 0 时判断按键按下
    if((KEY1) || (!KEY2))  //判断按键是否按下 
    {
        if(KEY1)
        {
            Key_Num = KEY1_DOWN;  // 按键KEY1按下返回按键1键值
        }
        else if(!KEY2)
        {
            Key_Num = KEY2_DOWN;  // 按键KEY2按下返回按键2键值
        }
    }
    return Key_Num; // 返回键值
}

/*
* @function: Key_Scan
* @param: None
* @retval: None
* @brief: 按键扫描 --- 按键三行消抖
*/
static void Key_Scan(void)
{
    static uint8_t Key_old;  // 上一次按键的键值

    Key_value = Key_Get_Value();  // 读取按键的键值
    Key_up = ~Key_value & (Key_old ^ Key_value);   // 按键的上升沿检测 只在按键抬起的瞬间有效 其他时刻都为零无效
    Key_down = Key_value & (Key_old ^ Key_value);  // 按键的下降沿检测 只在按键按下的瞬间有效 其他时刻都为零无效
    Key_old = Key_value;   // 记录上一次按键按下后的键值

    if(Key_down)   // 当有按键按下时
    {
        KEY.Key_Long_Count = 0;   // 将计时器清零 从零开始计时 
    }
    if(KEY.Key_Long_Count < 10)   // 如果计时时间小于1s 短按
    {
        switch(Key_up)        // 判断按键是否抬起 选择键值执行短按的相应程序
        {
            case KEY1_DOWN:
            {
                KEY.Key_Flag_Arr[0] = TRUE;
            }
            case KEY2_DOWN:
            {
                KEY.Key_Flag_Arr[1] = TRUE;
            }
            default:break;
        }
    }
    else   // 长按 计时时间超过1s
    {
        switch(Key_value)   //判断按键是否按下 选择按键的键值执行相应功能,如果这里改成key_up则按下松开才会执行下面
        {
            case KEY1_DOWN:
            {
                KEY.Key_Flag_Arr[2] = TRUE;
            }
            case KEY2_DOWN:
            {
                KEY.Key_Flag_Arr[3] = TRUE;
            }
            default:break;
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
    if(KEY.Key_Flag_Arr[0])
    {
        KEY.Key_Flag_Arr[0] = FALSE;
        Menu_Status = (Menu_Status - 1 + 1) % Page_MAX - 1 + 1 + 1; // 切换页面
        OLED.OLED_Clear();
    }
    else if(KEY.Key_Flag_Arr[1])
    {
        KEY.Key_Flag_Arr[1] = FALSE;
    }
    else if(KEY.Key_Flag_Arr[2])
    {
        KEY.Key_Flag_Arr[2] = FALSE;
    }
    else if(KEY.Key_Flag_Arr[3])
    {
        KEY.Key_Flag_Arr[3] = FALSE;
    }
}