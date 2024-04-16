 /******************************************************************************
 *
 * Project : Fan Controller System
 *
 * File Name: project3.c
 *
 * Description: control the fan speed based on the input of the LM35 temperature
 * 			    sensor
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include<util/delay.h>
#include<avr/io.h>
#include"lm35_sensor.h"
#include"dc_motor.h"
#include"lcd.h"
#include"adc.h"
#include"gpio.h"
#include"timer1.h"

#define MANUAL 	  0
#define AUTOMATIC 1

void timerTick();

/* variable to set time */
uint16 g_time=30;

int main()
{
	/* variable to control mode */
	uint8 mode = AUTOMATIC;
	/* variable to control fan speed */
	uint8 speed = 0;
	/* variable to indicate whether timer1 is working or not */
	uint8 timerOn=FALSE;
	/* variable to store temperature of LM35 */
	uint8 T;
	/* variable to configure ADC */
	ADC_ConfigType ADC_config;
	/* variable to configure Timer1 */
	Timer1_ConfigType Timer1_config;
	/* ADC configuration */
	ADC_config.prescaler=F_CPU_8;
	ADC_config.ref_volt=INTERNAL;
	/* initialize ADC */
	ADC_init(&ADC_config);
	/* Timer1 configuration */
	Timer1_config.initial_value=0;
	Timer1_config.compare_value=15635;
	Timer1_config.prescaler=CLK_1024;
	Timer1_config.mode=COMPARE;
	/* call back function for Timer1 interrupts */
	Timer1_setCallBack(timerTick);
	/* initialize motor pins */
	DcMotor_init();
	/* initialize LCD */
	LCD_init();
	LCD_displayString("A / ");
	//LCD_displayStringRowColumn(1, 3, "Temp =    C");
	/* set buttons pins input */
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_INPUT);

	GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_OUTPUT);
	/* set PIR pin input */
	GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_INPUT);
	/* global interrupt enable */
	SREG|=(1<<7);
	for(;;)
	{
		/* Turn the lamp on if there is motion */
		if(GPIO_readPin(PORTD_ID, PIN7_ID) == LOGIC_HIGH)
		{
			GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_HIGH);
		}
		else
		{
			GPIO_writePin(PORTC_ID, PIN0_ID, LOGIC_LOW);
		}
		/* when D2 button pressed toggle mode */
		if(GPIO_readPin(PORTD_ID, PIN2_ID) == LOGIC_LOW)
		{
			_delay_ms(30);
			if(GPIO_readPin(PORTD_ID, PIN2_ID) == LOGIC_LOW)
			{
				if(mode == AUTOMATIC)
				{
					mode = MANUAL;
					LCD_displayStringRowColumn(0,0,"M / ");
				}
				else
				{
					mode = AUTOMATIC;
					LCD_displayStringRowColumn(0,0,"A / ");
				}
			}
			_delay_ms(10);
		}

		/* when D3 button pressed and the mode is manual increase speed  */
		if(GPIO_readPin(PORTD_ID, PIN3_ID) == LOGIC_LOW && mode == MANUAL)
		{
			_delay_ms(30);
			if(GPIO_readPin(PORTD_ID, PIN3_ID) == LOGIC_LOW && mode == MANUAL)
			{
				speed++;
				/* max speed is 4 and start from 0 when exceeding 4 */
				if(speed == 5)
				{
					speed=0;
				}
			}
			_delay_ms(10);
		}

		/* when D4 button pressed toggle Timer1 */
		if(GPIO_readPin(PORTD_ID, PIN4_ID) == LOGIC_LOW)
		{
			_delay_ms(30);
			if(GPIO_readPin(PORTD_ID, PIN4_ID) == LOGIC_LOW)
			{
				if(!timerOn)
				{
					timerOn=TRUE;
					g_time=30;
					Timer1_init(&Timer1_config);
					LCD_displayStringRowColumn(1, 12,"T:");
					LCD_integerToString(g_time);
				}
				else
				{
					timerOn=FALSE;
					g_time=30;
					Timer1_deInit();
					LCD_displayStringRowColumn(1,12,"    ");
				}
			}
			_delay_ms(10);
		}

		if(timerOn)
		{
			LCD_moveCursor(1,14);
			LCD_integerToString(g_time);
			/* when D5 button pressed and the Timer is on increase time */
			if(GPIO_readPin(PORTD_ID, PIN5_ID) == LOGIC_LOW && g_time!=0)
			{
				_delay_ms(30);
				if(GPIO_readPin(PORTD_ID, PIN5_ID) == LOGIC_LOW &g_time!=0)
				{
					g_time+=30;
					if(g_time == 300)
					{
						g_time=30;
					}
				}
				_delay_ms(10);
			}

			/* stop motor when time reach 0 */
			if(g_time == 0)
			{
				speed = 0;
				Timer1_deInit();
			}
		}

		/* get sensor temperature */
		T=LM35_getTemperature();
		/* display the temperature on the LCD */
		LCD_displayStringRowColumn(1,0,"Temp = ");
		if(T < 10)
		{
			LCD_integerToString(T);
			LCD_displayString(" C");
		}
		else if(T < 100)
		{
			LCD_integerToString(T);
			LCD_displayCharacter('C');
		}
		if(mode == AUTOMATIC && g_time != 0)
		{
			/* control speed based on temperature */
			/* speed increases every 20 degrees */
			speed = T/20;
		}
		/* rotate motor with desired speed */
		DcMotor_Rotate(CW, speed * 25);
		/* display speed */
		LCD_displayStringRowColumn(0, 4, "Speed : ");
		LCD_displayCharacter(speed+'0');


	}
}

/*
 * Description :
 * call back function for Timer1 to act as the Interrupt Service Routine
 */
void timerTick()
{
	g_time--;
}
