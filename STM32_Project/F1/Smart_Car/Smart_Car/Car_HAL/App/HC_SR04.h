#ifndef __HC_SR04_H
#define __HC_SR04_H

typedef struct 
{
  float (*HC_SR04_Read_Distance)(void);
  float (*HC_SR04_Elude)(void);
} HC_SR04_t;



/* extern variables-----------------------------------------------------------*/

extern HC_SR04_t HC_SR04;


/* extern function prototypes-------------------------------------------------*/


#endif
/********************************************************
  End Of File
********************************************************/
