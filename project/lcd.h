 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_
#include"std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* configuration */
#define LCD_NUM_OF_BITS_MODE 4

#define LCD_RS_PORT_ID PORTA_ID
#define LCD_RS_PIN_ID PIN1_ID

#define LCD_E_PORT_ID PORTA_ID
#define LCD_E_PIN_ID PIN2_ID

#define LCD_DATA_PORT_ID PORTA_ID
#if(LCD_NUM_OF_BITS_MODE == 4)
#define LCD_DATA_PIN_ID PIN3_ID
#endif
/* LCD commands */
#define LCD_DISABLE_CURSOR 			  0x0C
#define LCD_CLEAR_SCREEN 			  0x01
#define LCD_SET_CURSOR_LOCATION		  0x80
#define LCD_2LINES_8BITS_MODE		  0x38
#define LCD_2LINES_4BITS_MODE         0x28
#define LCD_2LINES_4BITS_MODE_INIT1   0x33
#define LCD_2LINES_4BITS_MODE_INIT2   0x32

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * initialize the LCD ports
 * configure 2 lines 8 bit mode
 * clear the screen and disable cursor
 */
void LCD_init(void);

/*
 * Description :
 * send a command to the LCD
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * display a character on the LCD
 */
void LCD_displayCharacter(uint8 character);

/*
 * Description :
 * display a string on the LCD;
 */
void LCD_displayString(const sint8* string);

/*
 * Description :
 * display a string in a specific location
 */
void LCD_displayStringRowColumn(uint8 row, uint8 column,const sint8* string);


/*
 * Description :
 * convert integers to characters then display it
 */
void LCD_integerToString(int num);

/*
 * Description :
 * clear the screen of the LCD
 */
void LCD_clearScreen(void);

/*
 * Description :
 * move the LCD cursor to the desired location
 */
void LCD_moveCursor(uint8 row, uint8 column);
#endif /* LCD_H_ */
