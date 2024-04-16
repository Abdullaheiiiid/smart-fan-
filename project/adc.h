 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for the ADC driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#ifndef ADC_H_
#define ADC_H_
#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_REFERENCE_VOLTAGE 2.56
#define ADC_MAXIMUM_VALUE     1023
/*******************************************************************************
 * 								Types Declarations
 *******************************************************************************/
typedef enum{
	AREF=0, AVCC=1, INTERNAL=3
}ADC_ReferenceVolatge;

typedef enum{
	F_CPU_2=1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32, F_CPU_64, F_CPU_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * initialize the ADC with no interrupts
 */
void ADC_init(const ADC_ConfigType* config);

/*
 * Description :
 *	read analog value from specified channel and convert it to digital
 */
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
