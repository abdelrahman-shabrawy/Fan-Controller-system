/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC_MOTOR driver
 *
 * Author: Abdelrahman Shabrawy
 *
 *******************************************************************************/
#include "../../HAL/DC_MOTOR/dc_motor.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, PIN_OUTPUT);

	/* Motor is stop at the beginning */
	GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_LOW);
}

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/
 * or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on
 * the required speed value
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* check the speed in range of 0 :100
	 * and convert it to duty cycle and send it to PWM driver
	 * */
	if((speed >= 0) && (speed <= 100))
	{
		PWM_Timer0_Start((uint8)(speed*2.55));
	}
	/* check the motor direction and set the pins as required in data sheet */
	switch (state)
	{
	case STOP :
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_LOW);
		break;
	case CW :

		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_LOW);
		break ;
	case A_CW :

		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_A_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OPUT_PORT_ID, DC_MOTOR_OPUT_B_PIN_ID, LOGIC_HIGH);
		break ;
	}
}
