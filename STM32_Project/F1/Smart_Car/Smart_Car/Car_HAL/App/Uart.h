#ifndef __UART_H
#define __UART_H





/* extern variables-----------------------------------------------------------*/

extern uint8_t Usart1_ReadBuf[];
extern uint8_t Usart1_ReadCount;
extern void UART_JSON_Parser(void);
extern uint8_t Usart_WaitRessFinish(void);
extern uint8_t Usart3_ReceiveData;
extern uint8_t Usart3String[];
extern uint8_t Swerve;

/* extern function prototypes-------------------------------------------------*/




#endif
/********************************************************
  End Of File
********************************************************/
