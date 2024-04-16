 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for LCD driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#include"lcd.h"
#include"gpio.h"
#include<util/delay.h>
#include"common_macros.h"
#include<stdlib.h>

/*
 * Description :
 * initialize the LCD ports
 * configure 2 lines 8 bit mode
 * clear the screen and disable cursor
 */
void LCD_init(void)
{
	/* configure RS pin output */
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	/* configure enable pin output */
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
#if (LCD_NUM_OF_BITS_MODE == 8)
	/* configure data port output for 8 bit operations */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
	/* choose 2 lines 8 bits mode */
	LCD_sendCommand(LCD_2LINES_8BITS_MODE);
#elif (LCD_NUM_OF_BITS_MODE == 4)
	/* configure data pins output for 8 bit operations */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+1, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+2, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+3, PIN_OUTPUT);

	/* send 4 bits initialization */
	LCD_sendCommand(LCD_2LINES_4BITS_MODE_INIT1);
	LCD_sendCommand(LCD_2LINES_4BITS_MODE_INIT2);
	/* choose 2 lines 4 bits mode */
	LCD_sendCommand(LCD_2LINES_4BITS_MODE);
#endif
	_delay_ms(20);
	LCD_sendCommand(LCD_DISABLE_CURSOR);
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/*
 * Description :
 * send a command to the LCD
 */
void LCD_sendCommand(uint8 command)
{
	/* set RS to low to send a command */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	/* set enable bit to high */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	/* send the command */
#if (LCD_NUM_OF_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_ms(1);

	/* set enable bit to low */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif (LCD_NUM_OF_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID, GET_BIT(command, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+1, GET_BIT(command, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+2, GET_BIT(command, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+3, GET_BIT(command, 7));
	_delay_ms(1);

	/* set enable bit to low*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

	/* set enable bit to high */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID, GET_BIT(command, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+1, GET_BIT(command, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+2, GET_BIT(command, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+3, GET_BIT(command, 3));
	_delay_ms(1);

	/* set enable bit to low */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#endif
}

/*
 * Description :
 * display a character on the LCD
 */
void LCD_displayCharacter(uint8 character)
{
	/* set RS to high to send a character */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	/* set enable bit to high */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	/* send the character */
#if (LCD_NUM_OF_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT_ID, character);
	_delay_ms(1);

	/* set enable bit to low */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#elif (LCD_NUM_OF_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID, GET_BIT(character, 4));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+1, GET_BIT(character, 5));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+2, GET_BIT(character, 6));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+3, GET_BIT(character, 7));
	_delay_ms(1);

	/* set enable bit to low*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

	/* set enable bit to high */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID, GET_BIT(character, 0));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+1, GET_BIT(character, 1));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+2, GET_BIT(character, 2));
	GPIO_writePin(LCD_DATA_PORT_ID, LCD_DATA_PIN_ID+3, GET_BIT(character, 3));
	_delay_ms(1);

	/* set enable bit to low */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
#endif
}

/*
 * Description :
 * display a string on the LCD;
 */
void LCD_displayString(const sint8* string)
{
	for(; *string!='\0'; string++)
	{
		LCD_displayCharacter(*string);
	}
}

/*
 * Description :
 * display a string in a specific location
 */
void LCD_displayStringRowColumn(uint8 row, uint8 column,const sint8* string)
{
	LCD_moveCursor(row, column);
	LCD_displayString(string);
}

/*
 * Description :
 * convert integers to characters then display it
 */
void LCD_integerToString(int num)
{
	char buff[16];
	itoa(num, buff, 10);
	LCD_displayString((const uint8*)buff);
}

/*
 * Description :
 * clear the screen of the LCD
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/*
 * Description :
 * move the LCD cursor to the desired location
 */
void LCD_moveCursor(uint8 row, uint8 column)
{
	switch(row)
	{
	case 0:
		LCD_sendCommand(LCD_SET_CURSOR_LOCATION | column);
		break;
	case 1:
		LCD_sendCommand(LCD_SET_CURSOR_LOCATION | (column + 0x40));
		break;
	case 3:
		LCD_sendCommand(LCD_SET_CURSOR_LOCATION | (column + 0x10));
		break;
	case 4:
		LCD_sendCommand(LCD_SET_CURSOR_LOCATION | (column + 0x50));
		break;
	}
}
