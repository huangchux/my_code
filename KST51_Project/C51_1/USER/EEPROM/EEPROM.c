#include "AllHead.h"

///*******************************************************************************
//* �� �� �� : EEPROM_write_one_byte
//* �������� : �� EEPROM ָ����ַд��һ������
//* �� �� : addr:д�����ݵ�Ŀ�ĵ�ַ
//          dat:Ҫд�������
//* �� �� : ��
//*******************************************************************************/
//void EEPROM_write_one_byte(u8 addr,u8 dat)
//{
//	iic_start();
//	iic_write_byte(0xA0);  //����д����(ǰ��4λ�̶���������λ��gnd������0)
//	iic_wait_ack();
//	iic_write_byte(addr);  //����д��ַ
//	iic_wait_ack();
//	iic_write_byte(dat);   //�����ֽ�
//	iic_wait_ack();
//	iic_stop();            //����һ��ֹͣ����
//	Delay1ms(10);
//}


///*******************************************************************************
//* �� �� �� : EEPROM_read_one_byte
//* �������� : �� EEPROM ָ����ַ����һ������
//* �� �� : addr:��ʼ�����ĵ�ַ
//* �� �� : ����������
//*******************************************************************************/
//u8 EEPROM_read_one_byte(u8 addr)
//{
//	u8 receive = 0;
//	iic_start();
//	iic_write_byte(0xA0);  //����д����(Ѱ�Ҵӻ�) ���һλΪ0��ʾ������ӻ�д����
//	iic_wait_ack();
//	iic_write_byte(addr);  //��EEPROMָ��һ����ַ(��Ҫ���յ����ݴ�ŵ������ַ)
//	iic_wait_ack();
//	iic_start();           //�ٴ���������
//  iic_write_byte(0xA1);	 //�������ģʽ   ���һλΪ1��ʾ�����ɴӻ�������
//	iic_wait_ack();
//	receive = iic_read_byte(addr);  //��ȡ�ֽ�
//	iic_stop();            //����һ��ֹͣ����
//	return receive;        //���ض�ȡ������
//}




///**
//  * @brief  AT24C02д��һ���ֽ�
//  * @param  WordAddress Ҫд���ֽڵĵ�ַ
//  * @param  Data Ҫд�������
//  * @retval ��
//  */
//void EEPROM_WriteByte(u8 addr,u8 Data)
//{
//	I2C_Start();
//	I2C_SendByte(0xA0);  //����д����(ǰ��4λ�̶���������λ��gnd������0)
//	I2C_ReceiveAck();
//	I2C_SendByte(addr);  //����д��ַ
//	I2C_ReceiveAck();
//	I2C_SendByte(Data);  //�����ֽ�
//	I2C_ReceiveAck();
//	I2C_Stop();          //����һ��ֹͣ����
//}

///**
//  * @brief  AT24C02��ȡһ���ֽ�
//  * @param  WordAddress Ҫ�����ֽڵĵ�ַ
//  * @retval ����������
//  */
//u8 EEPROM_ReadByte(u8 addr)
//{
//	u8 Data;
//	I2C_Start();
//	I2C_SendByte(0xA0);  //����д����(Ѱ�Ҵӻ�) ���һλΪ0��ʾ������ӻ�д����
//	I2C_ReceiveAck();
//	I2C_SendByte(addr);  //��EEPROMָ��һ����ַ(��Ҫ���յ����ݴ�ŵ������ַ)
//	I2C_ReceiveAck();
//	I2C_Start();         //�ٴ���������
//	I2C_SendByte(0xA1);  //�������ģʽ   ���һλΪ1��ʾ�����ɴӻ�������
//	I2C_ReceiveAck();
//	Data=I2C_ReceiveByte();  //��ȡ�ֽ�
//	I2C_SendAck(1);
//	I2C_Stop();          //����һ��ֹͣ����
//	return Data;         //���ض�ȡ������
//}