/**
  *************************************************************************************************
  * @file       LCD_customChar_table.h
  * @author     SPSE Havirov
  * @version    1.0.0
  * @date       11-April-2023 [v0.1]
  * @history    Viz CHANGELOG.md
  * @brief      Definovani vlastnich znaku pro LCD s radicem HD44780.
  *
  *************************************************************************************************
  * @attention
  *
  *   Pro generovani vlastnich znaku a jejich hexa kodu mozno vyuzit napriklad:
  *     https://maxpromer.github.io/LCD-Character-Creator/
  *
  *************************************************************************************************
  * @copyright  Copyright SPSE Havirov (c) 2023 *
  ***********************************************
*/

uint8_t fullChar[] =
{
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F		// xxx 11111
};

uint8_t emptyChar[] =
{
	0x00,		// xxx 00000
	0x00,		// xxx 00000
	0x00,		// xxx 00000
	0x00,		// xxx 00000
	0x00,		// xxx 00000
	0x00,		// xxx 00000
	0x00,		// xxx 00000
	0x00,		// xxx 00000
};

uint8_t batteryFull[] =
{
	0x0E,		// xxx 01110
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F,		// xxx 11111
	0x1F		// xxx 11111
};
