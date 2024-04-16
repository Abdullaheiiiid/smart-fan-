 /******************************************************************************
 *
 * Module: TIMER0 on PWM mode
 *
 * File Name: pwm.h
 *
 * Description: Header file for TIMER0 PWM driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_
#include"std_types.h"
/*******************************************************************************
 * 							Functions Prototypes
 *******************************************************************************/
/*
 * Description :
 * initialize timer0 with non-inverting PWM mode
 * setup duty cycle
 * generate 500hz frequency
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
