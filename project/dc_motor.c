 /******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Source file for DC_MOTOR driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"dc_motor.h"
#include"gpio.h"
#include"pwm.h"

/*
 * Description :
 * setup the direction for the two motor pins through the GPIO driver
 */
void DcMotor_init(void)
{
	/* set motor pins as output */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID+1, PIN_OUTPUT);
	/* stop the motor at the beginning */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID+1, LOGIC_LOW);
}

/*
 * Description :
 * a function to choose motor state(ON/OFF, clock wise / anti clock wise)
 * and control speed
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	switch(state)
	{
	case STOP :
		/* stop motor */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID+1, LOGIC_LOW);
		break;
	case CW :
		/* rotate clock wise */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID+1, LOGIC_LOW);
		break;
	case A_CW :
		/* rotate anti clock wise */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_ID+1, LOGIC_HIGH);
		break;
	}
	PWM_Timer0_Start(speed);
}
