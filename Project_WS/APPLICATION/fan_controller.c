/*
 ============================================================================
 Name        : Mini_Project3.c
 Author      : Abdelrahman Shabrawy
 Description : FAN Controller Project
 Date        : 25/06/2023
 ============================================================================
 */
/* INCLUDE HARDWARE ABSTRCTION LAYERS WHICH ARE LCD , LM35_SENSOR AND DC_MOTOR  */
#include "../HAL/LM35_SENSOR/lm35_sensor.h"
#include "../HAL/DC_MOTOR/dc_motor.h"
#include "../HAL/LCD/lcd.h"
/* INCLUDE MICROCONTROLLER ABSTRCTION LAYERS WHICH ARE ADC and pwm */
#include "../MCAL/ADC/adc.h"
#include "../MCAL/PWM/pwm.h"
#include "../LIBRARIES/std_types.h"

int main(void)
{
	/* Create configuration structure for ADC driver */
	ADC_ConfigType ADC_configrations = {Internal_Voltage_Reference,prescaler_F_CPU_8,POLLING,Free_Running};

	uint8 tempraureReading = 0;
	/* Initialize  the LCD , ADC and DC_MOTOR driver */
	LCD_init();
	ADC_init(&ADC_configrations);
	DcMotor_Init();
	/*	Display the Initialize statues on the LCD  */
	LCD_moveCursor(0, 3);
	LCD_displayString("Fan is OFF");
	LCD_moveCursor(1, 3);
	LCD_displayString("Temp =     C");

	while(1)
	{
		/* Get the LM35 Temperature sensor reading */
		tempraureReading = LM35_getTemperature();
		/* Check the Temperature value to work as required from the requirements data   */
		if(tempraureReading < 30)
		{
			/* if the Temperature less than 30 stop the fan*/
			DcMotor_Rotate(STOP, 0);
			/* display the temp and fan statues in LCD*/
			LCD_moveCursor(0, 10);
			LCD_displayString("OFF");
			LCD_moveCursor(1,10);
			if(tempraureReading >= 100)
			{
				LCD_intgerToString(tempraureReading);
			}
			else
			{
				LCD_intgerToString(tempraureReading);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}
		/* if the Temperature bigger than 30  and less than 60
		 * turn fan on(CW direction) and set the speed to 25 of the fan*/

		else if((tempraureReading >= 30) && (tempraureReading < 60) )
		{
			/* turn on the fan with 25% of its maximum speed. */
			DcMotor_Rotate(CW,25);
			/* display the temp and fan statues in LCD*/
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1,10);
			if(tempraureReading >= 100)
			{
				LCD_intgerToString(tempraureReading);
			}
			else
			{
				LCD_intgerToString(tempraureReading);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}

		}
		/* if the Temperature bigger than 60  and less than 90
		 * turn fan on(CW direction) and set the speed to 50 of the fan*/

		else if((tempraureReading >= 60) &&(tempraureReading < 90))
		{
			/* turn on the fan with 50% of its maximum speed. */
			DcMotor_Rotate(CW,50);
			/* display the temp and fan statues in LCD*/
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1,10);
			if(tempraureReading >= 100)
			{
				LCD_intgerToString(tempraureReading);
			}
			else
			{
				LCD_intgerToString(tempraureReading);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}

		}
		/* if the Temperature bigger than 90  and less than 120
		 * turn fan on(CW direction) and set the speed to 75 of the fan*/

		else if((tempraureReading >= 90) &&(tempraureReading < 120))
		{

			/* turn on the fan with 75% of its maximum speed. */
			DcMotor_Rotate(CW,75);
			/* display the temp and fan statues in LCD*/
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1,10);
			if(tempraureReading >= 100)
			{
				LCD_intgerToString(tempraureReading);
			}
			else
			{
				LCD_intgerToString(tempraureReading);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}
		/* if the Temperature bigger than 120
		 * turn fan on(CW direction) and set the speed to 100 of the fan*/

		else if(tempraureReading >= 120)
		{
			/* turn on the fan with 100% of its maximum speed. */
			DcMotor_Rotate(CW,100);
			/* display the temp and fan statues in LCD*/
			LCD_moveCursor(0, 10);
			LCD_displayString("ON ");
			LCD_moveCursor(1,10);
			if(tempraureReading >= 100)
			{
				LCD_intgerToString(tempraureReading);
			}
			else
			{
				LCD_intgerToString(tempraureReading);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}
	}
}
