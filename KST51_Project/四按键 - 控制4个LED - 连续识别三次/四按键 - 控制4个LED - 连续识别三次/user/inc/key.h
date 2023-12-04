#ifndef _KEY_H_
#define _KEY_H_

typedef unsigned char u8; //对系统默认数据类型进行重命名

#define NO_KEY 0XFF   //表示按键未按下

#define KEY_PORT	P2  //宏定义按键端口

u8 Key_Scan();

#endif
