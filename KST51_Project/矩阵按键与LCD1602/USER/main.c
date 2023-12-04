#include <reg52.h>
#include <stdio.h>
#include <string.h>

//对系统默认数据类型进行重命名
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

//定义KEY引脚
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;
sbit KeyOut1 = P2^3;
sbit KeyOut2 = P2^2;
sbit KeyOut3 = P2^1;
sbit KeyOut4 = P2^0;

//定义LCD1602引脚
#define LCD1602_DB	P0
sbit LCD1602_RS = P1^0;
sbit LCD1602_RW = P1^1;
sbit LCD1602_E = P1^5;

//定义TIM变量
u8 T0RH = 0;  //T0 重载值的高字节
u8 T0RL = 0;  //T0 重载值的低字节

//定义KEY变量
u8 code KeyCodeMap[4][4] =   //矩阵按键编号到标准键盘键码的映射表
{
	  { '1', '2', '3', 0x26 }, //数字键 1、数字键 2、数字键 3、向上键
    { '4', '5', '6', 0x25 }, //数字键 4、数字键 5、数字键 6、向左键
    { '7', '8', '9', 0x28 }, //数字键 7、数字键 8、数字键 9、向下键
    { '0', 0x1B, 0x0D, 0x27 } //数字键 0、ESC 键、 回车键、 向右键
};

u8 pdata Key_state[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //按键当前状态
u16 Number = 0;

/***************************************** 函数声明区 *****************************************/
void Time0_Init(u16 ms);
void LCD_WaitReady();
void LCD_WriteCmd(u8 cmd);
void LCD_WriteDat(u8 dat);
void LCD_SetCursor(u8 x,u8 y);
void LCD_Showstr(u8 x,u8 y,u8 *str);
void LCD_Init();
void Key_scan();
void Key_driver();
void Key_Action(u8 keycode);
u8 LongToString(u8 *str,u32 dat);
void LCD_AreaClear(u8 x,u8 y, u8 len);

/***************************************** 主函数 *****************************************/

void main()
{
	Time0_Init(1);  //配置 T0 定时 1ms
	EA = 1;         //开总中断
	LCD_Init();     //初始化液晶
	while(1)
	{
		Key_driver();  //调用按键驱动
	}
}

/* T0 中断服务函数，执行按键扫描 */
void Time0() interrupt 1
{
	TH0 = T0RH; //重新加载重载值
	TL0 = T0RL;
	Key_scan(); //按键扫描函数
}

/***************************************** TIM *****************************************/

/* 配置并启动T0，ms-T0定时时间 */
void Time0_Init(u16 ms)
{
	u32 temp = 0;                        //临时变量
	temp = 11059200 / 12;                //定时器计数频率
	temp = (temp * ms) / 1000;           //计算所需的计数值
	temp = 65536 - temp;	               //计算定时器重载值
	temp += 18;	                         //补偿中断响应延时造成的误差
	T0RH = (unsigned char)(temp >> 8);   //定时器重载值拆分为高低字节
	T0RL = (unsigned char)temp;
	TMOD &= 0xF0;   //清零T0的控制位
	TMOD |= 0x01;   //配置T0为模式1
	TH0 = T0RH;     //加载T0重载值
	TL0 = T0RL;
	ET0 = 1;        //使能T0中断
	TR0 = 1;        //启动T0
}

/***************************************** LCD1602 *****************************************/

/* 等待液晶准备好 */
void LCD_WaitReady()    //读状态：RS = L，R/W = H，E = H
{
	u8 sta = 0;           //定义一个状态变量
	LCD1602_DB = 0xFF;
	LCD1602_RS = 0;
	LCD1602_RW = 1;
	do  //do while语句是先执行一次语句，再对循环条件进行判断
	{
		LCD1602_E = 1;     //使能
		sta = LCD1602_DB;  //读取状态字
		LCD1602_E = 0;     //读完撤销使能，防止液晶输出数据干扰 P0 总线
	}while(sta & 0x80);  //最高位等于 1 表示液晶正忙，重复检测直到其等于 0 为止
}

/* 向 LCD1602 液晶写入一字节命令，cmd-待写入命令值 */
void LCD_WriteCmd(u8 cmd) //写指令：RS = L，R/W = L，D0~D7 = 指令码，E = 高脉冲
{
	LCD_WaitReady();
	LCD1602_RS = 0;
	LCD1602_RW = 0;
	LCD1602_DB = cmd;
	LCD1602_E = 1;
	LCD1602_E = 0;
}

/* 向 LCD1602 液晶写入一字节数据，dat-待写入数据值 */
void LCD_WriteDat(u8 dat)  //写数据：RS = H，R/W = L，D0~D7 = 数据，E = 高脉冲
{
	LCD_WaitReady();
	LCD1602_RS = 1;
	LCD1602_RW = 0;
	LCD1602_DB = dat;
	LCD1602_E = 1;
	LCD1602_E = 0;
}

/* 设置显示 RAM 起始地址，亦即光标位置，(x,y)-对应屏幕上的字符坐标 */
void LCD_SetCursor(u8 x,u8 y)
{
	u8 addr;
	if(0 == y)           //由输入的屏幕坐标计算显示RAM的地址
	{
		addr = 0x00 + x;   //第一行字符地址从0x00起始
	}
	else
	{
		addr = 0x40 + x;   //第二行字符地址从0x40起始
	}
	LCD_WriteCmd(addr | 0x80); //设置RAM地址
}

/* 在液晶上显示字符串，(x,y)-对应屏幕上的起始坐标，str-字符串指针，len-需显示的字符长度 */
void LCD_Showstr(u8 x,u8 y,u8 *str)
{
	LCD_SetCursor(x,y);   //设置起始地址
	while(*str != '\0')
	{
		LCD_WriteDat(*str++);  //先取str指向的数据然后进入写数据函数，然后str自加1,优先级一样从右往左
	}
}

/* 初始化 1602 液晶 */
void LCD_Init()
{
	LCD_WriteCmd(0x38);  //16*2显示，5*7点阵，8位数据接口
	LCD_WriteCmd(0x0C);  //显示器开，光标关闭，闪烁关闭	0000 1100
	LCD_WriteCmd(0x06);  //文字不动，地址自动+1 0000 0110
	LCD_WriteCmd(0x01);  //清屏
}

/* 长整型数转换为字符串，str-字符串指针，dat-待转换数，返回值-字符串长度 */
u8 LongToString(u8 *str,u32 dat)
{
	signed char i = 0;
	u8 len = 0;
	u8 buf[12];
	do
	{
		buf[i++] = dat % 10;  //先转换为低位在前的十进制数组
		dat /= 10;
	}while(dat > 0);
	len += i;         //i 最后的值就是有效字符的个数
	while(i-- > 0)    //将数组值转换为 ASCII 码反向拷贝到接收指针上
	{
		*str++ = buf[i] + '0';
	}
	*str = '\0';  //添加字符串结束符
	return len;   //返回字符串长度
}

/* 区域清除，清除从(x,y)坐标起始的 len 个字符位 */
void LCD_AreaClear(u8 x,u8 y, u8 len)
{
	LCD_SetCursor(x,y);  //设置起始地址
	while(len--)         //连续写入空格
	{
		LCD_WriteDat(' ');
	}
}


/***************************************** KEY *****************************************/

/* 按键扫描函数，需在定时中断中调用 */
void Key_scan()
{
	u8 i = 0;
	static u8 KeyOut = 0;  //矩阵按键扫描输出索引
	static u8 Keybuf[4][4] = {{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
	{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF}};  //矩阵按键扫描缓冲区
	
	//将一行的 4 个按键值移入缓冲区
	Keybuf[KeyOut][0] = (Keybuf[KeyOut][0] << 1) | KeyIn1;
	Keybuf[KeyOut][1] = (Keybuf[KeyOut][1] << 1) | KeyIn2;
	Keybuf[KeyOut][2] = (Keybuf[KeyOut][2] << 1) | KeyIn3;
	Keybuf[KeyOut][3] = (Keybuf[KeyOut][3] << 1) | KeyIn4;
	//消抖后更新按键状态
	for(i = 0; i < 4; i++)  //每行 4 个按键，所以循环 4 次
	{
		if(0x00 == (Keybuf[KeyOut][i] & 0x0F))
		{
			//连续 4 次扫描值为 0，即 4*4ms 内都是按下状态时，可认为按键已稳定的按下
			Key_state[KeyOut][i] = 0;
		}
		else if(0x0F == (Keybuf[KeyOut][i] & 0x0F))
		{
			//连续 4 次扫描值为 1，即 4*4ms 内都是弹起状态时，可认为按键已稳定的弹起
			Key_state[KeyOut][i] = 1;
		}
	}
	//执行下一次的扫描输出
	KeyOut++;  //输出索引递增
	KeyOut = KeyOut & 0x03;
	switch(KeyOut)  //根据索引，释放当前输出引脚，拉低下次的输出引脚
	{
		case 0:KeyOut4 = 1;KeyOut1 = 0;break;
		case 1:KeyOut1 = 1;KeyOut2 = 0;break;
		case 2:KeyOut2 = 1;KeyOut3 = 0;break;
		case 3:KeyOut3 = 1;KeyOut4 = 0;break;
	}
}

/* 按键驱动函数，检测按键动作，调度相应动作函数，需在主循环中调用 */
void Key_driver()
{
	u8 i,j;
	static u8 backup[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}; //按键值备份，保存前一次的值
	for(i = 0; i < 4; i++)  //循环扫描 4*4 的矩阵按键
	{
		for(j = 0; j < 4; j++)
		{
			if(backup[i][j] != Key_state[i][j]) //当前值与前次值不相等说明此时按键有动作
			{
				if(backup[i][j] != 0)  //前次值不等于0，则当前值等于0，按键按下
				{
					Key_Action(KeyCodeMap[i][j]);
				}
				backup[i][j] = Key_state[i][j]; //更新前一次的备份值
			}
		}
	}
}

/* 按键动作函数，根据键码执行相应的操作，keycode-按键键码 */
void Key_Action(u8 keycode)  //按键动作函数，根据键码执行相应动作
{
	u8 str[20];
	u8 len = 0;
	if((keycode >= '0') && (keycode <= '9'))  //输入0~9
	{
		len = LongToString(str,keycode - '0'); //操作数转换为字符串 keycode - '0'表示转换为整数
		LCD_AreaClear(0,0,16 - len);           //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,str); 
	}
	if(0x26 == keycode)  //向上键
	{
		len = strlen("UP");              // 计算字符串长度
		LCD_AreaClear(0,0,16 - len);     //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,"UP");
	}
	else if(0x28 == keycode) //向下键
	{
		len = strlen("DOWN");
		LCD_AreaClear(0,0,16 - len);     //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,"DOWN");
	} 
	else if(0x25 == keycode) //向左键
	{
		len = strlen("LEFT");
		LCD_AreaClear(0,0,16 - len);     //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,"LEFT");
		
	} 
	else if(0x27 == keycode) //向右键
	{
		len = strlen("RIGHT");
		LCD_AreaClear(0,0,16 - len);     //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,"RIGHT");
	} 
	else if(0x0D == keycode) //回车键
	{
		len = strlen("ENTER");
		LCD_AreaClear(0,0,16 - len);     //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,"ENTER");
	} 
	else if(0x1B == keycode)  //Esc键
	{
		len = strlen("ESC");
		LCD_AreaClear(0,0,16 - len);     //清除第一行字符串右边的字符位
		LCD_Showstr(0,0,"ESC");
	}
}