 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Abdelrahman Shabrawy
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
/* INCLUDE MICROCONTROLLER ABSTRCTION LAYERS WHICH IS ADC */
#include "adc.h"
#include "../../LIBRARIES/common_macros.h" /* To use the macros like SET_BIT */

#ifdef interrupt
/* INCLUDE AVR LIBRARIES TO USE INTERRUPT AND INTURREPT REGISTERS */
#include <avr/interrupt.h> /* For ADC ISR */

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult = 0;
/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
		g_adcResult = ADC;
}
#endif
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/* ADMUX Register Bits Description:
		 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
		 * ADLAR   = 0 right adjusted
		 * MUX4:0  = 00000 to choose channel 0 as initialization
		 */
	ADMUX = (ADMUX & 0X3F) | ((Config_Ptr->ref_volt)<<6);
	CLEAR_BIT(ADMUX,ADLAR);
	ADMUX = (ADMUX & 0XE0) | (0);

	/* ADCSRA Register Bits Description: */

	/* set bit num(7,5,4) as required mood
	 * in polling mood
	 *  ADEN    = 1 Enable ADC
	 *	ADIE    = 0 Disable ADC Interrupt
	 *	ADATE   = 1 Enable Auto Trigger
	 *	in interrupt mood
	 *	ADEN    = 1 Enable ADC
	 *	ADATE   = 1 Enable Auto Trigger
	 *	ADIE    = 1 Enable ADC Interrupt
	 */
	ADCSRA = (ADCSRA & 0XA8) | (Config_Ptr->mood);
	/* ADPS2:0 = clock to choose ADC_Clock  --> ADC must operate in range 50-200Khz */
	ADCSRA = (ADCSRA & 0XF8) | (Config_Ptr->prescaler);
	/* ADTS2:0 = trigger to chooser ADC_trigger source */
	SFIOR = (SFIOR & 0X1F) | ((Config_Ptr->trigger)<<5);
}
#ifdef interrupt
void ADC_readChannel(uint8 Ch_num)
#endif
#ifndef interrupt
uint16 ADC_readChannel(uint8 Ch_num)
#endif
{
	/* Input channel number must be from 0 --> 7
	   Clear first 5 bits in the ADMUX
	   (channel number MUX4:0 bits)
	   before set the required channel
	   Choose the correct channel by setting the channel
	   number in MUX4:0 bits */
	ADMUX=(ADMUX & 0XE0) | (Ch_num & 0x07);
	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);

#ifndef interrupt
	/* Wait for conversion to complete, ADIF becomes '1' */
	while (bit_is_clear(ADCSRA,ADIF));
	/* Clear ADIF by write '1' to it :) */
	SET_BIT(ADCSRA,ADIF);
	/* Read the digital value from the data register */
	return ADC;
#endif
}

