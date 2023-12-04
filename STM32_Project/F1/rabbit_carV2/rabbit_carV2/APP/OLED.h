#ifndef __OLED_H
#define __OLED_H
#include "AllHead.h"

// OLED的IIC地址(SA0 = 0) --- 0111 1000
#define OLED096_ADDR       0x78
// OLED参数(宽度，高度)
#define OLED096_WIDTH      128
#define OLED096_HEIGHT     64

// 最大显示字符数
#define OLED_Dis_MAX_Char 16

// 字体大小
typedef enum
{
    ASCII_SIZE_16 = 16,
} ASCII_Size_et;

// 最大只能显示4行
typedef enum
{
    OLED096_Line1 = 0,  
    OLED096_Line2 = 2,
    OLED096_Line3 = 4,
    OLED096_Line4 = 6,
} OLED_Line_et;

typedef struct
{
  void (*OLED_Init)(void);                                                      // OLED初始化
  void (*OLED_Clear)(void);                                                     // 清屏
  void (*OLED_Show_String)(uint8_t, OLED_Line_et, const char *, ASCII_Size_et); // OLED显示字符串
  void (*OLED_Show_CHN)(uint8_t, OLED_Line_et, const char *);                   // OLED显示单个汉字
  void (*OLED_Fill_Space)(uint8_t *);                                           // 补全空格
} OLED_st;

extern OLED_st OLED;

#endif
