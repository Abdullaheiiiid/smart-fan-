 /******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for DC_MOTOR driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include"std_types.h"
/*******************************************************************************
 * 								Definitions
 *******************************************************************************/
#define DC_MOTOR_PORT_ID PORTB_ID
#define DC_MOTOR_PIN_ID	 PIN0_ID
/*******************************************************************************
 * 								Types Declarations
 *******************************************************************************/
typedef enum{
	STOP, CW, A_CW
}DcMotor_State;

/*******************************************************************************
 * 							Functions Prototypes
 *******************************************************************************/
/*
 * Description :
 * setup the direction for the two motor pins through the GPIO driver
 */
void DcMotor_init(void);

/*
 * Description :
 * a function to choose motor state(ON/OFF, clock wise / anti clock wise)
 * and control speed
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DC_MOTOR_H_ */
