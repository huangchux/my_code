/***************************************************************************
 * File: OLED.c
 * Author: Emily
 * Date: 2023/12/2
 * description: OLED
****************************************************************************/
#include "AllHead.h"
#include "OLED_Font.h"

/* Public variables==========================================================*/
IIC_Parameter_st OLED_Parameter_IIC; // 注册结构体

/* Private function prototypes===============================================*/
static void OLED_Write_CMD(uint8_t CMD);                                                           // OLED写命令
static void OLED_Write_Data(uint8_t Data);                                                         // OLED写数据
static void OLED_Init(void);                                                                       // OLED初始化
static void OLED_Clear(void);                                                                      // 清屏
static void OLED_Set_Pos(uint8_t Page, uint8_t Seg);                                               // OLED设置坐标
static void OLED_Show_String(uint8_t x, OLED_Line_et y, const char *p_Str, ASCII_Size_et ch_size); // OLED显示字符串
static void OLED_Show_CHN(uint8_t x, OLED_Line_et y, const char *p_Str);                           // OLED显示单个汉字
static void OLED_Fill_Space(uint8_t *str);                                                         // 补全空格

/* Public variables==========================================================*/
OLED_st OLED = 
{
    .OLED_Init = &OLED_Init,
    .OLED_Clear = &OLED_Clear,
    .OLED_Show_String = &OLED_Show_String,
    .OLED_Show_CHN = &OLED_Show_CHN,
    .OLED_Fill_Space = &OLED_Fill_Space
};

/*
* @function: OLED_Write_CMD
* @param: CMD -> 待写入命令
* @retval: None
* @brief: OLED写命令
*/
static void OLED_Write_CMD(uint8_t CMD)
{
    bsp_IIC.IIC_Start(&OLED_Parameter_IIC);
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, OLED096_ADDR);  // R/W#=0
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, 0x00);          // Co=0,D/C#=0
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, CMD);
    bsp_IIC.IIC_Stop(&OLED_Parameter_IIC);
}

/*
* @function: OLED_Write_Data
* @param: Data -> 待写入数据
* @retval: None
* @brief: OLED写数据
*/
static void OLED_Write_Data(uint8_t Data)
{
    bsp_IIC.IIC_Start(&OLED_Parameter_IIC);
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, OLED096_ADDR);  // R/W#=0
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, 0x40);          // Co=0,D/C#=1
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, Data);
    bsp_IIC.IIC_Stop(&OLED_Parameter_IIC);
}

/*
* @function: OLED_Init
* @param: None
* @retval: None
* @brief: OLED初始化
*/
static void OLED_Init(void)
{
    bsp_IIC.IIC_Registered(&OLED_Parameter_IIC, OLED_SCL_GPIO_Port, OLED_SCL_Pin, OLED_SDA_GPIO_Port, OLED_SDA_Pin);  // 注册IIC设备
    Public.Public_Delay_ms(300);

    OLED_Write_CMD(0xAE); // OLED休眠
    OLED_Write_CMD(0x00); // 设置低列地址
    OLED_Write_CMD(0x10); // 设置高列地址
    OLED_Write_CMD(0x40); // 设置起始地址线
    OLED_Write_CMD(0xB0); // set page address
    OLED_Write_CMD(0x81); // 设置对比度
    OLED_Write_CMD(0xFF); //--128
    OLED_Write_CMD(0xA1); // 0xa0左右反置 0xa1正常
    OLED_Write_CMD(0xA6); // normal / reverse
    OLED_Write_CMD(0xA8); // 设置多路复用(1 to 64)
    OLED_Write_CMD(0x3F); // 1/32 duty
    OLED_Write_CMD(0xC8); // Com scan direction
    OLED_Write_CMD(0xD3); // 设置显示的偏移映射内存计数器
    OLED_Write_CMD(0x00); //

    OLED_Write_CMD(0xD5); // 设置显示时钟分频比/振荡器频率
    OLED_Write_CMD(0x80); // 设置分频比例，时钟设置为100帧/秒

    OLED_Write_CMD(0xD8); // set area color mode off
    OLED_Write_CMD(0x05); //

    OLED_Write_CMD(0xD9); // 预充电时间
    OLED_Write_CMD(0xF1); // 预充电为15个脉冲，释放为1个脉冲

    OLED_Write_CMD(0xDA); // 引脚设置硬件配置
    OLED_Write_CMD(0x12); //

    OLED_Write_CMD(0xDB); // 设置VCOM电平
    OLED_Write_CMD(0x30); //
    // 唤醒
    OLED_Write_CMD(0x8D); // 设置电荷泵
    OLED_Write_CMD(0x14); // 开启电荷泵

    OLED_Write_CMD(0xAF); // OLED唤醒(AE是OLED休眠)

    OLED_Clear();    // 清屏
}

/*
* @function: OLED_Clear
* @param: None
* @retval: None
* @brief: OLED清屏
*/
static void OLED_Clear(void)
{
    uint8_t Page, Seg;

    for (Page = 0; Page < 8; Page++)
    {
        OLED_Write_CMD(0xB0 + Page); // 一共8页(行)
        OLED_Write_CMD(0x00);        // 低
        OLED_Write_CMD(0x01);        // 高

        for (Seg = 0; Seg < 128; Seg++)
        {
            OLED_Write_Data(0x00);
        }
    }
}

/*
* @function: OLED_Set_Pos
* @param: Page -> 行 Seg -> 列
* @retval: None
* @brief: OLED设置坐标
*/
static void OLED_Set_Pos(uint8_t Page, uint8_t Seg)
{
    OLED_Write_CMD(0xB0 + Seg);
    OLED_Write_CMD(((Page & 0xF0) >> 4) | 0x10); // 高4位
    OLED_Write_CMD((Page & 0x0F));               // 低4位
}

/*
* @function: OLED_Show_String
* @param: x -> 列 y -> 行 p_Str -> 要显示的字符串 ch_size -> 字体大小
* @retval: None
* @brief: OLED显示字符串
*/
static void OLED_Show_String(uint8_t x, OLED_Line_et y, const char *p_Str, ASCII_Size_et ch_size)
{
    uint8_t i = 0;
    uint8_t c = 0;

    if (ch_size == 16)
    {
        while (p_Str[i] != '\0')
        {
            c = p_Str[i++] - ' ';
            OLED_Set_Pos(x, y);
            for (uint8_t j = 0; j < 8; j++)
                OLED_Write_Data(ucASCII_16x8[c * 16 + j]);
            OLED_Set_Pos(x, y + 1);
            for (uint8_t j = 0; j < 8; j++)
                OLED_Write_Data(ucASCII_16x8[c * 16 + j + 8]);

            x += 8;
            if (x > 120)
            {
                x = 0;
                y += 2;
            }
        }
    }
}

/*
* @function: OLED_Show_CHN
* @param: x -> 列 y -> 行  p_Str -> 单个汉字字符串
* @retval: None
* @brief: // OLED显示单个汉字
*/
static void OLED_Show_CHN(uint8_t x, OLED_Line_et y, const char *p_Str)
{
    uint16_t usCHN_Number; // 字库中汉字数量
    uint16_t usIndex;      // 字库中的汉字索引
    uint8_t i;

    // 统计汉字的位置
    usCHN_Number = sizeof(CHN_16x16) / sizeof(Oled_Font16x16_t);
    // 查找汉字的位置
    for (usIndex = 0; usIndex < usCHN_Number; usIndex++)
    {
        if ((CHN_16x16[usIndex].Index[0] == *p_Str) && (CHN_16x16[usIndex].Index[1] == *(p_Str + 1))) // 因为一个汉字占两个字节
        {
            OLED_Set_Pos(x, y);
            for (i = 0; i < 16; i++)
            {
                OLED_Write_Data(CHN_16x16[usIndex].CHN_code[i]);
            }

            OLED_Set_Pos(x, y + 1);
            for (i = 0; i < 16; i++)
            {
                OLED_Write_Data(CHN_16x16[usIndex].CHN_code[i + 16]);
            }
            break;
        }
    }
}

/*
* @function: OLED_Fill_Space
* @param: *str -> 字符串
* @retval: None
* @brief: 补全空格
*/
static void OLED_Fill_Space(uint8_t *str)
{
	uint8_t len = 0;
	uint8_t i = 0;
	
	len = strlen((char*)str); // 计算传入字符串的长度
	
	if (OLED_Dis_MAX_Char == len) // 如果传入字符串的长度 = 最大显示字符数 则退出
	{
		return;
	}
	while (i < OLED_Dis_MAX_Char) // 小于最大显示字符数
	{
		if (0 == str[i])    // 如果遇到字符串结束符
		{
			str[i] = ' ';   // 将结束符替换为一个空格字符
		}
		i++;    // 循环计数器自增
	}
}