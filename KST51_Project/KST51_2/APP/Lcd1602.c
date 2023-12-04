//#include "AllHead.h"

///* 等待液晶准备好 */
//void Lcd_WaitReady() //读状态：RS = L，R/W = H，E = H
//{
//	u8 sta = 0;
//	LCD1602_DB = 0xFF; 
//	LCD1602_RS = 0;
//	LCD1602_RW = 1;
//	do                   //do while语句是先执行一次语句，再对循环条件进行判断
//	{
//		LCD1602_E = 1;     //使能
//		sta = LCD1602_DB;  //读取状态字
//		LCD1602_E = 0;     //读完撤销使能，防止液晶输出数据干扰 P0 总线
//	}while(sta & 0x80);  //最高位等于 1 表示液晶正忙，重复检测直到其等于 0 为止
//}

///* 向 LCD1602 液晶写入一字节命令，cmd-待写入命令值 */
//void Lcd_WriteCmd(u8 cmd) //写指令：RS = L，R/W = L，D0~D7 = 指令码，E = 高脉冲
//{
//	Lcd_WaitReady();
//	LCD1602_RS = 0;
//	LCD1602_RW = 0;
//	LCD1602_DB = cmd;
//	LCD1602_E = 1;
//	LCD1602_E = 0;
//}

///* 向 LCD1602 液晶写入一字节数据，dat-待写入数据值 */
//void Lcd_WriteDat(u8 dat) //写数据：RS = H，R/W = L，D0~D7 = 数据，E = 高脉冲
//{
//	Lcd_WaitReady();
//	LCD1602_RS = 1;
//	LCD1602_RW = 0;
//	LCD1602_DB = dat;
//	LCD1602_E = 1;
//	LCD1602_E = 0;
//}

///* 设置显示 RAM 起始地址，亦即光标位置，(x,y)-对应屏幕上的字符坐标 */
//void Lcd_SetCursor(u8 x, u8 y)
//{
//	u8 addr;
//	if(0 == y)          //由输入的屏幕坐标计算显示RAM的地址
//	{
//		addr = 0x00 + x;  //第一行字符地址从0x00起始
//	}
//	else
//	{
//		addr = 0x40 + x;  //第二行字符地址从0x40起始
//	}
//	Lcd_WriteCmd(addr | 0x80); //设置RAM地址
//}

///* 在液晶上显示字符串，(x,y)-对应屏幕上的起始坐标，str-字符串指针 */
//void Lcd_ShowStr(u8 x, u8 y, u8 *str)
//{
//	Lcd_SetCursor(x,y);  //设置起始地址
//	while(*str != '\0')         
//	{
//		Lcd_WriteDat(*str++); //先取str指向的数据然后进入写数据函数，然后str自加1,优先级一样从右往左
//	}
//}

///* 区域清除，清除从(x,y)坐标起始的 len 个字符位 */
////void Lcd_AreaClear(u8 x, u8 y, u8 len)
////{
////	Lcd_SetCursor(x,y);  //设置起始地址
////	while(len--)         //连续写入空格
////	{
////		Lcd_WriteDat(' ');
////	}
////}

///* 初始化 1602 液晶 */
//void Lcd1602_Init()
//{
//	Lcd_WriteCmd(0x38); //16*2显示，5*7点阵，8位数据接口
//	Lcd_WriteCmd(0x0C); //显示器开，光标关闭，闪烁关闭	0000 1100
//	Lcd_WriteCmd(0x06); //文字不动，地址自动+1 0000 0110
//	Lcd_WriteCmd(0x01); //清屏
//}

