#ifndef __SG90_H
#define __SG90_H
#include "AllHead.h"

typedef enum
{
    Angle_0 = 0x00,   // 0
    Angle_45 = 0x01,  // 45
    Angle_90 = 0x02,  // 90
    Angle_135 = 0x03, // 135
    Angle_180 = 0x04, // 180
} SG90_Angle_et;

typedef struct
{
    void (*SG90_Init)(void);
    void (*SG90_Set_Angle)(SG90_Angle_et angle);
} SG90_st;

extern SG90_st SG90;

#endif
