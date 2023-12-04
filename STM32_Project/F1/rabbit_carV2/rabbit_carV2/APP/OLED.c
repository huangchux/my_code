/***************************************************************************
 * File: OLED.c
 * Author: Emily
 * Date: 2023/11/12
 * description: 
****************************************************************************/
#include "AllHead.h"
#include "OLED_Font.h"

/* Private variables=========================================================*/
IIC_Parameter_st OLED_Parameter_IIC;    // ע��ṹ��

/* Private function prototypes===============================================*/
static void OLED_Write_CMD(uint8_t CMD);                                                           // OLEDд����
static void OLED_Write_Data(uint8_t Data);                                                         // OLEDд����
static void OLED_Init(void);                                                                       // OLED��ʼ��
static void OLED_Clear(void);                                                                      // ����
static void OLED_Set_Pos(uint8_t Page, uint8_t Seg);                                               // OLED��������
static void OLED_Show_String(uint8_t x, OLED_Line_et y, const char *p_Str, ASCII_Size_et ch_size); // OLED��ʾ�ַ���
static void OLED_Show_CHN(uint8_t x, OLED_Line_et y, const char *p_Str);                           // OLED��ʾ��������
static void OLED_Fill_Space(uint8_t *str);                                                         // ��ȫ�ո�

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
* @param: CMD -> ��д������
* @retval: None
* @brief: OLEDд����
*/
static void OLED_Write_CMD(uint8_t CMD)
{
    bsp_IIC.IIC_Start(&OLED_Parameter_IIC);
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, OLED096_ADDR);        // R/W#=0
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, 0x00);       // Co=0,D/C#=0
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, CMD);
    bsp_IIC.IIC_Stop(&OLED_Parameter_IIC);    
}

/*
* @function: OLED_Write_Data
* @param: Data -> ��д������
* @retval: None
* @brief: OLEDд����
*/
static void OLED_Write_Data(uint8_t Data)
{
    bsp_IIC.IIC_Start(&OLED_Parameter_IIC);
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, OLED096_ADDR);        // R/W#=0
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, 0x40);       // Co=0,D/C#=1
    bsp_IIC.IIC_Write_Byte(&OLED_Parameter_IIC, Data);
    bsp_IIC.IIC_Stop(&OLED_Parameter_IIC);    
}

/*
* @function: OLED_Init
* @param: None
* @retval: None
* @brief: OLED��ʼ��
*/
static void OLED_Init(void)
{
    bsp_IIC.IIC_Registered(&OLED_Parameter_IIC, OLED_SCL_GPIO_Port, OLED_SCL_Pin, OLED_SDA_GPIO_Port, OLED_SDA_Pin);    // ע��IIC�豸
    Public.Public_Delay_ms(300); // �ϵ���ʱ
    
    OLED_Write_CMD(0xAE); // OLED����
    OLED_Write_CMD(0x00); // ���õ��е�ַ
    OLED_Write_CMD(0x10); // ���ø��е�ַ
    OLED_Write_CMD(0x40); // ������ʼ��ַ��
    OLED_Write_CMD(0xB0); // set page address
    OLED_Write_CMD(0x81); // ���öԱȶ�
    OLED_Write_CMD(0xFF); //--128
    OLED_Write_CMD(0xA1); // 0xa0���ҷ��� 0xa1����
    OLED_Write_CMD(0xA6); // normal / reverse
    OLED_Write_CMD(0xA8); // ���ö�·����(1 to 64)
    OLED_Write_CMD(0x3F); // 1/32 duty
    OLED_Write_CMD(0xC8); // Com scan direction
    OLED_Write_CMD(0xD3); // ������ʾ��ƫ��ӳ���ڴ������
    OLED_Write_CMD(0x00); //

    OLED_Write_CMD(0xD5); // ������ʾʱ�ӷ�Ƶ��/����Ƶ��
    OLED_Write_CMD(0x80); // ���÷�Ƶ������ʱ������Ϊ100֡/��

    OLED_Write_CMD(0xD8); // set area color mode off
    OLED_Write_CMD(0x05); //

    OLED_Write_CMD(0xD9); // Ԥ���ʱ��
    OLED_Write_CMD(0xF1); // Ԥ���Ϊ15�����壬�ͷ�Ϊ1������

    OLED_Write_CMD(0xDA); // ��������Ӳ������
    OLED_Write_CMD(0x12); //

    OLED_Write_CMD(0xDB); // ����VCOM��ƽ
    OLED_Write_CMD(0x30); //
    // ����
    OLED_Write_CMD(0x8D); // ���õ�ɱ�
    OLED_Write_CMD(0x14); // ������ɱ�

    OLED_Write_CMD(0xAF); // OLED����(AE��OLED����)

    OLED_Clear();    // ����
}

/*
* @function: OLED_Clear
* @param: None
* @retval: None
* @brief: OLED����
*/
static void OLED_Clear(void)
{
    uint8_t Page, Seg;

    for (Page = 0; Page < 8; Page++)
    {
        OLED_Write_CMD(0xB0 + Page); // һ��8ҳ(��)
        OLED_Write_CMD(0x00);        // ��
        OLED_Write_CMD(0x01);        // ��

        for (Seg = 0; Seg < 128; Seg++)
        {
            OLED_Write_Data(0x00);
        }
    }
}

/*
* @function: OLED_Set_Pos
* @param: Page -> �� Seg -> ��
* @retval: None
* @brief: OLED��������
*/
static void OLED_Set_Pos(uint8_t Page, uint8_t Seg)
{
    OLED_Write_CMD(0xB0 + Seg);
    OLED_Write_CMD(((Page & 0xF0) >> 4) | 0x10); // ��4λ
    OLED_Write_CMD((Page & 0x0F));               // ��4λ
}

/*
* @function: OLED_Show_String
* @param: x -> �� y -> �� p_Str -> Ҫ��ʾ���ַ��� ch_size -> �����С
* @retval: None
* @brief: OLED��ʾ�ַ���
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
* @param: x -> �� y -> ��  p_Str -> ���������ַ���
* @retval: None
* @brief: // OLED��ʾ��������
*/
static void OLED_Show_CHN(uint8_t x, OLED_Line_et y, const char *p_Str)
{
    uint16_t usCHN_Number; // �ֿ��к�������
    uint16_t usIndex;      // �ֿ��еĺ�������
    uint8_t i;

    // ͳ�ƺ��ֵ�λ��
    usCHN_Number = sizeof(CHN_16x16) / sizeof(Oled_Font16x16_t);
    // ���Һ��ֵ�λ��
    for (usIndex = 0; usIndex < usCHN_Number; usIndex++)
    {
        if ((CHN_16x16[usIndex].Index[0] == *p_Str) && (CHN_16x16[usIndex].Index[1] == *(p_Str + 1))) // ��Ϊһ������ռ�����ֽ�
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
* @param: *str -> �ַ���
* @retval: None
* @brief: ��ȫ�ո�
*/
static void OLED_Fill_Space(uint8_t *str)
{
	uint8_t len = 0;
	uint8_t i = 0;
	
	len = strlen((char*)str); // ���㴫���ַ����ĳ���
	
	if (OLED_Dis_MAX_Char == len) // ��������ַ����ĳ��� = �����ʾ�ַ��� ���˳�
	{
		return;
	}
	while (i < OLED_Dis_MAX_Char) // С�������ʾ�ַ���
	{
		if (0 == str[i])    // ��������ַ���������
		{
			str[i] = ' ';   // ���������滻Ϊһ���ո��ַ�
		}
		i++;    // ѭ������������
	}
}