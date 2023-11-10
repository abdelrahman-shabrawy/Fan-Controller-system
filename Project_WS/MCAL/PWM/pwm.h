/*
 * pwm.h
 *
 *  Created on: Jul 1, 2023
 *      Author: amoha
 */

#ifndef MCAL_PWM_PWM_H_
#define MCAL_PWM_PWM_H_

#include "../GPIO/gpio.h"
#include "../../LIBRARIES/std_types.h"

void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* MCAL_PWM_PWM_H_ */
