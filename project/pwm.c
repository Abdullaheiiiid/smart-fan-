 /******************************************************************************
 *
 * Module: TIMER0 on PWM mode
 *
 * File Name: pwm.h
 *
 * Description: source file for TIMER0 PWM driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"pwm.h"
#include"gpio.h"
#include<avr/io.h>

/*
 * Description :
 * initialize timer0 with non-inverting PWM mode
 * setup duty cycle
 * generate 500hz frequency
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* setup OC0 pin as output */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	/* select non-inverting fast PWM mode with prescaler F_CPU/8 */
	TCCR0=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS02);
	TCNT0=0;
	OCR0=((uint16)duty_cycle * 255) / 100;
}
