 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: Header file for TIMER1 driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include"std_types.h"
/*******************************************************************************
 * 							   Types Declarations
 *******************************************************************************/
typedef enum{
	NO_CLK, CLK_1, CLK_8, CLK_64, CLK_256, CLK_1024, EXTERNAL_FALLING_EDGE, EXTERNAL_RISING_EDGE
}Timer1_Prescaler;

typedef enum{
	NORMAL, COMPARE
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
}Timer1_ConfigType;
/*******************************************************************************
 * 							   Functions Prototype
 *******************************************************************************/
/*
 * Description :
 * a function to initiate timer1 with desired configuration(prescaler, mode, initial register values)
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * a function to deactivate timer1
 */
void Timer1_deInit(void);

/*
 * Description :
 * a function to set the call back function pointer
 */
void Timer1_setCallBack(void (*a_ptr)(void));
#endif /* TIMER1_H_ */
