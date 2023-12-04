#ifndef __ENCODER_H
#define __ENCODER_H
#include "AllHead.h"

// 轮子的直径(cm)
#define Whell_Diameter 7 
// π
#define PI 3.14f
// 周长
#define Perimeter (float)(Whell_Diameter * PI)

typedef struct
{
    float Mileage;                      // 里程数(cm)
    float Encoder_Left_Speed;           // 左编码器电机速度
    float Encoder_Right_Speed;          // 右编码器电机速度

    void (*Encoder_Init)(void);         // 编码器初始化
    void (*Encoder_Get_Speed)(void);    // 获取编码器速度 
    void (*Encoder_Get_Mileage)(void);  // 获取里程数
} Encoder_st;   


extern Encoder_st Encoder;

#endif
