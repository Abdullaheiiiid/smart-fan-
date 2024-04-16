 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for ADC driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"adc.h"
#include<avr/io.h>
#include"common_macros.h"

/*
 * Description :
 * initialize the ADC with no interrupts
 */
void ADC_init(const ADC_ConfigType* Config_Ptr)
{
	/* choose voltage reference voltage */
	ADMUX=(Config_Ptr->ref_volt<<6);
	/* enable ADC and set prescaler */
	ADCSRA=(1<<ADEN)|(Config_Ptr->prescaler);
}


/*
 * Description :
 *	read analog value from specified channel and convert it to digital
 */
uint16 ADC_readChannel(uint8 ch_num)
{
	/* choosing the channel */
	ADMUX=(ADMUX & 0xE0) | (0x1F & ch_num);
	/* start ADC conversion */
	SET_BIT(ADCSRA, ADSC);
	/* waiting for conversion to finish */
	while(BIT_IS_CLEAR(ADCSRA, ADIF));
	/* clear interrupt flag */
	SET_BIT(ADCSRA, ADIF);
	/* return converted data */
	return ADC;
}

