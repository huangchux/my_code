#ifndef __LED_H
#define __LED_H

//定义枚举类型
typedef enum
{
	LED1 = (uint8_t)0x01,
	// LED2 = (uint8_t)0x02,
	// LED3 = (uint8_t)0x03,
}LED_Num_t;

//定义结构体类型
typedef struct
{
	void (*LED_ON)(uint8_t);     //打开
	void (*LED_OFF)(uint8_t);    //关闭
	void (*LED_Flip)(uint8_t);   //翻转
} LED_t;



/* extern variables-----------------------------------------------------------*/

extern LED_t LED;

/* extern function prototypes-------------------------------------------------*/


#endif
/********************************************************
  End Of File
********************************************************/
