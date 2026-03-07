/*
 * LCD.c
 *
 *  Created on: Mar 7, 2026
 *      Author: madhu
 */
#include"main.h"
#include"LCD.h"

void LCD_Write_String(char str[])
{
	for (int i=0;str[i]!='\0';i++)
	{
		LCD_Write_Data(str[i]);
	}
}

void LCD_Initialization()
{
		HAL_Delay(20);
		LCD_Write_Command(0x33);
		HAL_Delay(1);
		LCD_Write_Command(0x32);
		LCD_Write_Command(0x0C);
		LCD_Write_Command(0x01);
}
void LCD_HigerNibble(unsigned char ch)
{
		HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (ch & 0x8));
		HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (ch & 0x4));
		HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (ch & 0x2));
		HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (ch & 0x1));
}
void LCD_LowerNibble(unsigned char ch)
{
		HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (ch & 0x8));
		HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (ch & 0x4));
		HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (ch & 0x2));
		HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (ch & 0x1));
}


void LCD_Write_Data(unsigned char ch)
{
		HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, RESET);
		HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, SET);
		LCD_HigerNibble(ch>>4);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, RESET);
		LCD_LowerNibble(ch);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, RESET);

}

void LCD_Write_Command(unsigned char ch)
{
		HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, RESET);
		HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, RESET);
		LCD_HigerNibble(ch>>4);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, RESET);
		LCD_LowerNibble(ch);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, SET);
		HAL_Delay(10);
		HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, RESET);

}
