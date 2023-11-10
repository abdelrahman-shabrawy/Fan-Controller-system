 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../../LIBRARIES/std_types.h"


#ifdef	interrupt
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */

extern volatile uint16 g_adcResult;

#endif

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	AREF,AVCC,Reserved,Internal_Voltage_Reference
}ADC_ReferenceVoltage;

typedef enum
{
	POLLING = 0XA0,INTERRUPT=0XA8
}ADC_MoodType;

typedef enum
{
	prescaler_F_CPU_2,prescaler_F_CPU_2_1,prescaler_F_CPU_4,\
	prescaler_F_CPU_8,prescaler_F_CPU_16,prescaler_F_CPU_32,\
	prescaler_F_CPU_64,prescaler_F_CPU_128
}ADC_Prescaler;

typedef enum
{
	Free_Running,Analog_Comparator,External_Interrupt_Req_0,Timer_Counter0_Compare_Match,\
	Timer_Counter0_Overflow,Timer_Counter1_Compare_Match_B,Timer_Counter1_Overflow,\
	Timer_Counter1_Capture_Event
}ADC_TriggerSourceType;

typedef struct
{
	ADC_ReferenceVoltage ref_volt;;
	ADC_Prescaler prescaler;
	ADC_MoodType mood;
	ADC_TriggerSourceType trigger;
}ADC_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
#ifdef interrupt
void ADC_readChannel(uint8 Ch_num);
#endif
#ifndef interrupt
uint16 ADC_readChannel(uint8 Ch_num);
#endif
#endif /* ADC_H_ */
