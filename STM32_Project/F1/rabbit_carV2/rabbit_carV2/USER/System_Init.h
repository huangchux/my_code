#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H
#include "AllHead.h"

typedef struct
{
    void (*Hardware_Init)(void);    // 硬件初始化
} System_Init_st;

extern System_Init_st System_Init;

#endif