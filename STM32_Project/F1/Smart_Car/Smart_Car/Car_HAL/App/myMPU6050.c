/***************************************************************************
 * File: myMPU6050.c
 * Author: Luckys.
 * Date: 2023/09/14
 * description: MPU6050
****************************************************************************/
#include "AppHeader.h"

/*====================================static function declaration area BEGIN====================================*/
static uint8_t MPU_Init(void);

static uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr);
static uint8_t MPU_Set_Accel_Fsr(uint8_t fsr);
static uint8_t MPU_Set_LPF(uint16_t lpf);
static uint8_t MPU_Set_Rate(uint16_t rate);

static short MPU_Get_Temperature(void);
static uint8_t MPU_Get_Gyroscope(short *gx, short *gy, short *gz);
static uint8_t MPU_Get_Accelerometer(short *ax, short *ay, short *az);

static uint8_t MPU_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
static uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
static uint8_t MPU_Write_Byte(uint8_t reg, uint8_t data);
static uint8_t MPU_Read_Byte(uint8_t reg);
/*====================================static function declaration area   END====================================*/

IIC_Data_t MPU6050_IIC;

MPU6050_st myMPU6050 = 
{
	.gyz_RealAngleSpeed = 0,
	.gyz_integral = 0,
	.gyro_x = 0,
	.gyro_y = 0,
	.gyro_z = 0,
	.MPU_Init = &MPU_Init,
	.MPU_Get_Gyroscope = &MPU_Get_Gyroscope,
	.MPU_Write_Len = &MPU_Write_Len,
	.MPU_Read_Len = &MPU_Read_Len
};


/*
* @function: MPU_Init
* @param: NONE
* @retval: ����ֵ:0,���óɹ� ����,����ʧ��
* @brief: MPU6050��ʼ��
*/
static uint8_t MPU_Init(void)
{
    uint8_t res;
	
    // ע��IIC
    IIC_Soft.IIC_Registered(&MPU6050_IIC, MPU6050_SCL_GPIO_Port, MPU6050_SCL_Pin, MPU6050_SDA_GPIO_Port, MPU6050_SDA_Pin);
    MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X80);	//��λMPU6050
    Public.Public_Delay_ms(100);
    MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X00);	//����MPU6050
    MPU_Set_Gyro_Fsr(2);					//�����Ǵ�����,��2000dps
    MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
    MPU_Set_Rate(200);						//���ò�����50Hz
    MPU_Write_Byte(MPU_INT_EN_REG, 0X00);	//�ر������ж�
    MPU_Write_Byte(MPU_USER_CTRL_REG, 0X00);	//I2C��ģʽ�ر�
    MPU_Write_Byte(MPU_FIFO_EN_REG, 0X00);	//�ر�FIFO
    MPU_Write_Byte(MPU_INTBP_CFG_REG, 0X80);	//INT���ŵ͵�ƽ��Ч
    res = MPU_Read_Byte(MPU_DEVICE_ID_REG);
    if(res == MPU_ADDR) //����ID��ȷ
    {
        MPU_Write_Byte(MPU_PWR_MGMT1_REG, 0X01);	//����CLKSEL,PLL X��Ϊ�ο�
        MPU_Write_Byte(MPU_PWR_MGMT2_REG, 0X00);	//���ٶ��������Ƕ�����
        MPU_Set_Rate(100);						//���ò�����Ϊ100Hz,����Ϊ10ms
    }
    else return 1;
    return 0;
}

/*
* @function: MPU_Set_Gyro_Fsr
* @param: fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
* @retval: ����ֵ:0,���óɹ� ����,����ʧ��
* @brief: ����MPU6050�����Ǵ����������̷�Χ
*/
static uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
    return MPU_Write_Byte(MPU_GYRO_CFG_REG, fsr << 3); //���������������̷�Χ
}

/*
* @function: MPU_Set_Accel_Fsr
* @param: fsr:0,��2g;1,��4g;2,��8g;3,��16g
* @retval: ����ֵ:0,���óɹ� ����,����ʧ��
* @brief: ����MPU6050���ٶȴ����������̷�Χ
*/
static uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
    return MPU_Write_Byte(MPU_ACCEL_CFG_REG, fsr << 3); //���ü��ٶȴ����������̷�Χ
}


/*
* @function: MPU_Set_LPF
* @param: lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
* @retval: ����ֵ:0,���óɹ� ����,����ʧ��
* @brief: ����MPU6050�����ֵ�ͨ�˲���
*/
static uint8_t MPU_Set_LPF(uint16_t lpf)
{
    uint8_t data = 0;
    if(lpf >= 188)data = 1;
    else if(lpf >= 98)data = 2;
    else if(lpf >= 42)data = 3;
    else if(lpf >= 20)data = 4;
    else if(lpf >= 10)data = 5;
    else data = 6;
    return MPU_Write_Byte(MPU_CFG_REG, data); //�������ֵ�ͨ�˲���
}
 
/*
* @function: MPU_Set_Rate
* @param: rate:4~1000(Hz)
* @retval: ����ֵ:0,���óɹ� ����,����ʧ��
* @brief: ����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
*/
static uint8_t MPU_Set_Rate(uint16_t rate)
{
    uint8_t data;
    if(rate > 1000)rate = 1000;
    if(rate < 4)rate = 4;
    data = 1000 / rate - 1;
    data = MPU_Write_Byte(MPU_SAMPLE_RATE_REG, data);	//�������ֵ�ͨ�˲���
    return MPU_Set_LPF(rate / 2);	//�Զ�����LPFΪ�����ʵ�һ��
}

/*
* @function: MPU_Get_Temperature
* @param: NONE
* @retval: �¶�ֵ(������100��)
* @brief: �õ��¶�ֵ
*/
static short MPU_Get_Temperature(void)
{
    uint8_t buf[2];
    short raw;
    float temp;
    MPU_Read_Len(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf);
    raw = ((uint16_t)buf[0] << 8) | buf[1];
    temp = 36.53 + ((double)raw) / 340;
    return temp * 100;;
}

/*
* @function: MPU_Get_Gyroscope
* @param: gx,gy,gz:������x,y,z���ԭʼ����(������)
* @retval: 0,���� ����,�������
* @brief: �õ�������ֵ(ԭʼֵ)--���ٶ�
*/
static uint8_t MPU_Get_Gyroscope(short *gx, short *gy, short *gz)
{
    uint8_t buf[6], res;
    res = MPU_Read_Len(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
    if(res == 0)
    {
        *gx = ((uint16_t)buf[0] << 8) | buf[1];
        *gy = ((uint16_t)buf[2] << 8) | buf[3];
        *gz = ((uint16_t)buf[4] << 8) | buf[5];	// 
    }
    return res;
}

/*
* @function: MPU_Get_Accelerometer
* @param: gx,gy,gz:������x,y,z���ԭʼ����(������)
* @retval: 0,���� ����,�������
* @brief: �õ����ٶ�ֵ(ԭʼֵ)--�Ǽ��ٶ�
*/
static uint8_t MPU_Get_Accelerometer(short *ax, short *ay, short *az)
{
    uint8_t buf[6], res;
    res = MPU_Read_Len(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf);
    if(res == 0)
    {
        *ax = ((uint16_t)buf[0] << 8) | buf[1];
        *ay = ((uint16_t)buf[2] << 8) | buf[3];
        *az = ((uint16_t)buf[4] << 8) | buf[5];
    }
    return res;;
}


/**********************************MPU6050 IIC�ײ㺯��**********************************/

/*
* @function: MPU_Write_Len
* @param: addr:������ַ reg:�Ĵ�����ַ len:д�볤�� buf:������
* @retval: 0,���� ����,�������
* @brief: IIC����д
*/
uint8_t static MPU_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    uint8_t i;

    IIC_Soft.IIC_Start(&MPU6050_IIC);
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, (addr << 1) | 0); // ����������ַ+д����
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, reg); // д�Ĵ�����ַ

    for (i = 0; i < len; i++)
    {
        IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, buf[i]); // ��������
    }
    IIC_Soft.IIC_Stop(&MPU6050_IIC);
    return 0;
}

/*
* @function: MPU_Read_Len
* @param: addr:������ַ reg:Ҫ��ȡ�ļĴ�����ַ len:Ҫ��ȡ�ĳ��� buf:��ȡ�������ݴ洢��
* @retval: 0,���� ����,�������
* @brief: IIC������
*/
static uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    IIC_Soft.IIC_Start(&MPU6050_IIC);
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, (addr << 1) | 0); // ����������ַ+д����
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, reg); // д�Ĵ�����ַ
    IIC_Soft.IIC_Start(&MPU6050_IIC);
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, (addr << 1) | 1); // ����������ַ+������

    while (len)
    {
        if (len == 1)
            *buf = IIC_Soft.IIC_Read_Byte(&MPU6050_IIC, NACK); // ������,����nACK
        else
            *buf = IIC_Soft.IIC_Read_Byte(&MPU6050_IIC, ACK); // ������,����ACK
        len--;
        buf++;
    }
    IIC_Soft.IIC_Stop(&MPU6050_IIC);
    return 0;
}

/*
* @function: MPU_Write_Byte
* @param: reg:�Ĵ�����ַ
* @retval:
* @brief: 0,����  ����,�������
*/
static uint8_t MPU_Write_Byte(uint8_t reg, uint8_t data)
{
    IIC_Soft.IIC_Start(&MPU6050_IIC);
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, (MPU_ADDR << 1) | 0); //����������ַ+д����
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, reg);	//д�Ĵ�����ַ
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, data);//��������
    IIC_Soft.IIC_Stop(&MPU6050_IIC);
    return 0;
}

/*
* @function: MPU_Read_Byte
* @param: reg:�Ĵ�����ַ
* @retval: ����������
* @brief:IIC��һ���ֽ�
*/
static uint8_t MPU_Read_Byte(uint8_t reg)
{
    uint8_t res;
    IIC_Soft.IIC_Start(&MPU6050_IIC);
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, (MPU_ADDR << 1) | 0); // ����������ַ+д����
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, reg);					// д�Ĵ�����ַ
    IIC_Soft.IIC_Start(&MPU6050_IIC);
    IIC_Soft.IIC_Write_Byte(&MPU6050_IIC, (MPU_ADDR << 1) | 1); // ����������ַ+������
    res = IIC_Soft.IIC_Read_Byte(&MPU6050_IIC, NACK);
    IIC_Soft.IIC_Stop(&MPU6050_IIC);
    return res;
}


