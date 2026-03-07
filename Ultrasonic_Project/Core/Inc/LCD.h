/*
 * LCD.h
 *
 *  Created on: Mar 7, 2026
 *      Author: madhu
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_



void LCD_Initialization();
void LCD_Write_String(char str[]);
void LCD_HigerNibble(unsigned char ch);
void LCD_LowerNibble(unsigned char ch);
void LCD_Write_Data(unsigned char ch);
void LCD_Write_Command(unsigned char ch);
#endif /* INC_LCD_H_ */
