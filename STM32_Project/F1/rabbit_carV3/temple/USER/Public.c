/***************************************************************************
 * File: Public.c
 * Author: Emily
 * Date: 2023/11/20
 * description: 公用的函数
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void Public_Delay_ms(uint16_t ms);
static void Public_Delay_us(uint16_t us);
static inline void Str_To_Float(const char *p_str, float *save_arr);

/* Public variables==========================================================*/
Public_st Public = 
{
    .Public_Delay_ms = &Public_Delay_ms,
    .Public_Delay_us = &Public_Delay_us,
    .Str_To_Float = &Str_To_Float,
};

/*
* @function: Public_Delay_ms
* @param: ms -> 要延时的时间
* @retval: None
* @brief: ms延时
*/
static void Public_Delay_ms(uint16_t ms)
{
    HAL_Delay(ms);
}

/*
* @function: Public_Delay_us
* @param: None
* @retval: None
* @brief: us延时
*/
static void Public_Delay_us(uint16_t us)
{
    uint8_t i = 0;

    while(us--)
    {
        for(i = 0; i < 2; i++);
    }
}

/*
* @function: fputc
* @param: None
* @retval: None
* @brief: 重定向printf函数(&必须要写)
*/
int fputc (int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);
    return ch;
}

/*
* @function: Str_To_Float
* @param: p_Str -> 待提取的字符串 save_var -> 提取结果存储地址
* @retval: None
* @brief: 提取字符串里面(等于号=)后面的浮点数
*/
// 使用 inline 关键字可以告诉编译器将函数内容插入到调用该函数的地方，而不是通过函数调用的方式来执行函数。这样可以减少函数调用的开销，提高代码的执行效率。
static inline void Str_To_Float(const char *p_str, float *save_arr)
{
    // 查找等号的位置，strchr 函数会在 p_Str 所指向的字符串中查找字符第一次出现的位置，如果找到了，则返回指向该字符的指针；如果未找到，则返回空指针
    const char* start = strchr(p_str, '=');

    if(start == NULL)
    {
        return;
    }
    sscanf(start + 1, "%f", save_arr); // 使用 sscanf 函数提取浮点数值
}