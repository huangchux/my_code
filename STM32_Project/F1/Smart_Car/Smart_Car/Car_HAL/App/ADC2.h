#ifndef __ADC2_H
#define __ADC2_H

typedef struct
{
    float (*ADC_Get_Battery_Voltage)(void);
} My_ADC2_t;

/* extern variables-----------------------------------------------------------*/

extern My_ADC2_t My_ADC2;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
