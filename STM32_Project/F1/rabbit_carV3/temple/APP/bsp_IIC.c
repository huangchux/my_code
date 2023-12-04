/***************************************************************************
 * File: bsp_IIC.c
 * Author: Emily
 * Date: 2023/12/1
 * description: 
****************************************************************************/
#include "AllHead.h"

/* Private function prototypes===============================================*/
static void IIC_Init(IIC_Parameter_st *dev);
static void IIC_Registered(IIC_Parameter_st *dev, GPIO_TypeDef *SCL_GPIOx, uint16_t SCL_GPIO_Pin, GPIO_TypeDef *SDA_GPIOx, uint16_t SDA_GPIO_Pin);
static void IIC_Start(IIC_Parameter_st *dev);
static void IIC_Stop(IIC_Parameter_st *dev);
static ACK_Value_et IIC_Write_Byte(IIC_Parameter_st *dev, uint8_t WR_Byte);
static uint8_t IIC_Read_Byte(IIC_Parameter_st *dev, ACK_Value_et ACK_Value);
static uint8_t IIC_Write_Buffer(IIC_Parameter_st *dev, uint8_t addr, uint8_t reg, uint32_t len, uint8_t *data);
static uint8_t IIC_Read_Buffer(IIC_Parameter_st *dev, uint8_t addr, uint8_t reg, uint32_t len, uint8_t *buf);

/* Public variables==========================================================*/
bsp_IIC_st bsp_IIC = 
{
    .IIC_Registered = &IIC_Registered,
    .IIC_Start = &IIC_Start,
    .IIC_Stop = &IIC_Stop,
    .IIC_Write_Byte = &IIC_Write_Byte,
    .IIC_Read_Byte = &IIC_Read_Byte,
    .IIC_Write_Buffer = &IIC_Write_Buffer,
    .IIC_Read_Buffer = &IIC_Read_Buffer
};

/*
* @function: IIC_Init
* @param: dev -> 结构体指针
* @retval: None
* @brief: IIC初始化
*/
static void IIC_Init(IIC_Parameter_st *dev)
{
    // 拉高SCL,SDA
    SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
}

/*
* @function: IIC_Registered
* @param: dev -> 待注册的结构体指针 SCL_GPIOx -> SCL引脚端口组 SCL_GPIOx -> SCL引脚 SDA_GPIOx -> SDA端口组 SDA_GPIO_Pin -> SDA引脚
* @retval: None
* @brief: IIC注册
*/
static void IIC_Registered(IIC_Parameter_st *dev, GPIO_TypeDef *SCL_GPIOx, uint16_t SCL_GPIO_Pin, GPIO_TypeDef *SDA_GPIOx, uint16_t SDA_GPIO_Pin)
{
    dev->SCL_GPIOx = SCL_GPIOx;
    dev->SCL_GPIO_Pin = SCL_GPIO_Pin;
    dev->SDA_GPIOx = SDA_GPIOx;
    dev->SDA_GPIO_Pin = SDA_GPIO_Pin;

    IIC_Init(dev);
}

/*
* @function: IIC_Start
* @param: dev -> 结构体指针
* @retval: None
* @brief: IIC起始信号
*/
static void IIC_Start(IIC_Parameter_st *dev)
{
    // SCL为高电平，SDA的下降沿为I2C起始信号
    SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);

    Public.Public_Delay_us(1);

    CLR_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
    Public.Public_Delay_us(10);

    CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    Public.Public_Delay_us(1);
}

/*
* @function: IIC_Stop
* @param: None
* @retval: None
* @brief: IIC停止信号
*/
static void IIC_Stop(IIC_Parameter_st *dev)
{
    // SCL为高电平，SDA的上升沿为I2C停止信号
    CLR_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
    SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    Public.Public_Delay_us(1);

    Public.Public_Delay_us(10);
    SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
}

/*
* @function: IIC_Write_Byte
* @param: dev -> 结构体指针 WR_Byte -> 待写入字节
* @retval: ACK_Value_t -> 从机应答值
* @brief: IIC写字节
*/
static ACK_Value_et IIC_Write_Byte(IIC_Parameter_st *dev, uint8_t WR_Byte)
{
    uint8_t i;
    ACK_Value_et ACK_Rspond; 

    // SCL为低电平时，SDA准备数据,接着SCL为高电平，读取SDA数据
	// 数据按8位传输，高位在前，利用for循环逐个接收
    for(i = 0; i < 8; i++)
    {
        // SCL清零，主机SDA准备数据
        CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
        Public.Public_Delay_us(1);

        if(0x80 == (WR_Byte & 0x80)) // 比较最高位
        {
            SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
        }
        else
        {
            CLR_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
        }
        Public.Public_Delay_us(1);

        // SCL置高，传输数据
        SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin); // 为1数据稳定等待下一次传输
        Public.Public_Delay_us(10);

        //准备发送下一比特位
        WR_Byte <<= 1; // 左移一位(将次高位移到最高位)
    }
    CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);  // 数据传输完毕，让SCL为0，使下一次数据可以改变并进行传输
    
    //释放SDA，等待从机应答
    SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);  // 8 位数据发送完后，主机释放 SDA，以检测从机应答
    Public.Public_Delay_us(1);

    SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);  // 拉高 SCL
    Public.Public_Delay_us(10);

    ACK_Rspond = (ACK_Value_et)READ_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin); // 读取此时的 SDA 值，即为从机的应答值

    CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);  // 再拉低 SCL 完成应答位，并保持住总线
    Public.Public_Delay_us(1);

    //返回从机的应答信号
    return ACK_Rspond;
}

/*
* @function: IIC_Read_Byte
* @param: dev -> 结构体指针 ACK_Value -> 主机回应值(控制是否继续读下去)
* @retval: None
* @brief: IIC读字节
*/
static uint8_t IIC_Read_Byte(IIC_Parameter_st *dev, ACK_Value_et ACK_Value)
{
    uint8_t RD_Byte = 0, i;

    // 接收数据
	// SCL为低电平时，SDA准备数据,接着SCL为高电平，读取SDA数据
	// 数据按8位传输，高位在前，利用for循环逐个接收
    for(i = 0; i < 8; i++)
    {
        // 准备接收下一比特位
        RD_Byte <<= 1;

        // SCL清零，从机SDA准备数据
        CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
        Public.Public_Delay_us(10);

        // SCL置高，获取数据
        SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
        Public.Public_Delay_us(10);

        RD_Byte |= READ_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
    }

    // SCL清零，主机准备应答信号
    CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    Public.Public_Delay_us(1);

    // 主机发送应答信号	
    if(ACK == ACK_Value) // 应答
    {
        CLR_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
    }
    else // 非应答
    {
        SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
    }
    Public.Public_Delay_us(1);

    SET_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    Public.Public_Delay_us(10);

    // 释放SDA数据线
	// SCL先清零，再释放SDA，防止连续传输数据时，从机错将SDA释放信号当成NACk信号
    CLR_SCL(dev->SCL_GPIOx, dev->SCL_GPIO_Pin);
    SET_SDA(dev->SDA_GPIOx, dev->SDA_GPIO_Pin);
    Public.Public_Delay_us(1);

    // 返回数据
    return RD_Byte;
}

/*
* @function: IIC_Write_Buffer
* @param: dev -> 结构体指针 addr -> 目标设备地址 reg -> 寄存器地址 len -> 要发送的数据长度 data -> 指向数据缓冲区的指针
* @retval: 0 --- 成功
* @brief: IIC写一串数据
*/
static uint8_t IIC_Write_Buffer(IIC_Parameter_st *dev, uint8_t addr, uint8_t reg, uint32_t len, uint8_t *data)
{
    uint32_t i;

    // 开始信号
    bsp_IIC.IIC_Start(dev);
    bsp_IIC.IIC_Write_Byte(dev, addr | 0x00);
    bsp_IIC.IIC_Write_Byte(dev, reg);

    for(i = 0; i < len; i++)
    {
        bsp_IIC.IIC_Write_Byte(dev, data[i]);
    }
    bsp_IIC.IIC_Stop(dev);

    return 0;
}

/*
* @function: IIC_Read_Buffer
* @param: dev -> 结构体指针 addr -> 目标设备地址 reg -> 寄存器地址 len -> 要读取的数据长度 buf -> 指向数据缓冲区的指针
* @retval: 0 --- 成功
* @brief: IIC读一串数据
*/
static uint8_t IIC_Read_Buffer(IIC_Parameter_st *dev, uint8_t addr, uint8_t reg, uint32_t len, uint8_t *buf)
{
    // 开始信号
    bsp_IIC.IIC_Start(dev);
    bsp_IIC.IIC_Write_Byte(dev, addr | 0x00);
    bsp_IIC.IIC_Write_Byte(dev, reg);
    Public.Public_Delay_us(5);

    bsp_IIC.IIC_Start(dev);
    bsp_IIC.IIC_Write_Byte(dev, addr | 0x01);   // 读操作

    while(len)
    {
        if(len > 1)
        {
            *buf = bsp_IIC.IIC_Read_Byte(dev, ACK);
        }
        else
        {
            *buf = bsp_IIC.IIC_Read_Byte(dev, NACK);
        }
        buf++;
        len--;
    }
    bsp_IIC.IIC_Stop(dev);
    return 0;
}
