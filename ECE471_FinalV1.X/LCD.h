/* 
 * File:   LCD.h
 * Author: rafay
 *
 * Created on March 26, 2023, 6:49 PM
 */

#ifndef LCD_H
#define	LCD_H

#include "SystemConfiguration.h"

#define LCD_EN_Delay 250//500

#define LCD_DATA_PORT_D TRISB
#define LCD_RS_D TRISBbits.RB5
#define LCD_EN_D TRISBbits.RB4
#define RS PORTBbits.RB5
#define EN PORTBbits.RB4

#define D4 PORTBbits.RB0
#define D5 PORTBbits.RB1
#define D6 PORTBbits.RB2
#define D7 PORTBbits.RB3


//==============================================
//-----[ Prototypes For All LCD Functions ]-----
 
void LCD_Init(void); // Initialize The LCD For 4-Bit Interface
void LCD_Clear(void); // Clear The LCD Display
void LCD_SL(void); // Shift The Entire Display To The Left
void LCD_SR(void); // Shift The Entire Display To The Right
 
void LCD_CMD(unsigned char); // Send Command To LCD
void LCD_DATA(unsigned char); // Send 4-Bit Data To LCD
void LCD_Set_Cursor(unsigned char, unsigned char); // Set Cursor Position
void LCD_Write_Char(char); // Write Character To LCD At Current Position
void LCD_Write_String(char*); // Write A String To LCD





#endif	/* LCD_H */

