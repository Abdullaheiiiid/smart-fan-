 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: Source file for TIMER1 driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include<avr/io.h>
#include<avr/interrupt.h>
#include"common_macros.h"
#include"timer1.h"
/*******************************************************************************
 * 						  Interrupt Service Routines
 *******************************************************************************/
static void  (*g_callBack)(void);
/* ISR for compare match interrupt */
ISR(TIMER1_COMPA_vect)
{
	(*g_callBack)();
}
/* ISR for overflow interrupt */
ISR(TIMER1_OVF_vect)
{
	(*g_callBack)();
}
/*******************************************************************************
 * 							  Functions Definitions
 *******************************************************************************/
/*
 * Description :
 * a function to initiate timer1 with desired configuration(prescaler, mode, initial register values)
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/* initializing timer 1 counter register */
	TCNT1 = Config_Ptr->initial_value;
	/* initializing compare register if compare mode specified */
	if(Config_Ptr->mode == COMPARE)
	{
		OCR1A = Config_Ptr->compare_value;
		/* enable compare match interrupt */
		TIMSK|=(1<<OCIE1A);
	}
	else
	{
		/* enable overflow interrupt */
		TIMSK|=(1<<TOIE1);
	}
	/* set FOC1A to 1 for non_PWM mode */
	TCCR1A|=(1<<FOC1A);
	/* set prescaler and choose mode of operation */
	/* note : WGM!0 and WGM11 are set to 0 in both normal and compare mode */
	TCCR1B= Config_Ptr->prescaler | (Config_Ptr->mode<<WGM12);
}

/*
 * Description :
 * a function to deactivate timer1
 */
void Timer1_deInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
}

/*
 * Description :
 * a function to set the call back function pointer
 */
void Timer1_setCallBack(void (*a_ptr)(void))
{
	g_callBack=a_ptr;
}
