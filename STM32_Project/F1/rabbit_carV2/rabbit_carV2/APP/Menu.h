#ifndef __MENU_H
#define __MENU_H
#include "AllHead.h"

// 页面数
#define Page_MAX 6

// 页面
typedef enum
{
    // 电量显示页面
    Page_Power = 0x01,
    // 显示编码器数据
    Page_Encoder = 0x02,
    // 显示寻迹灯的电平状态
    Page_Track_Light = 0x03,
    // 显示左电机的PID参数
    Page_Left_Motor_PID = 0x04,
    // 显示右电机的PID参数
    Page_Right_Motor_PID = 0x05,    
    // 显示寻迹PID的PID参数
    Page_Track_PID = 0x06,
} Menu_Status_et;

typedef struct
{
    void (*Menu_Init)(void);    // 页面初始化
    void (*Menu_Handler)(void); // 页面切换显示
} Menu_st;

extern Menu_st Menu;
extern Menu_Status_et Menu_Status;

#endif
