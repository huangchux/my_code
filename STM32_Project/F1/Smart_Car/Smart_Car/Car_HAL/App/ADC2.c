/* Includes ------------------------------------------------------------------*/
#include "AppHeader.h"

/* Private variables----------------------------------------------------------*/

float ADC_Get_Battery_Voltage(void);

/* Public variables-----------------------------------------------------------*/

My_ADC2_t My_ADC2 =
    {
        .ADC_Get_Battery_Voltage = ADC_Get_Battery_Voltage,
};

/* function prototypes--------------------------------------------------------*/

/**
 * @name
 * @param  None
 * @retval None
 * @brief
 */
float ADC_Get_Battery_Voltage(void)
{
    HAL_ADC_Start(&hadc2);
    if (HAL_OK == HAL_ADC_PollForConversion(&hadc2, 50))
    {
        return (float)HAL_ADC_GetValue(&hadc2) / 4096 * 3.3 * 5;
    }
    return -1;
}



/********************************************************
  End Of File
********************************************************/
