/**
 ******************************************************************************
 * @file    LcdCustomScroll_I2C.h
 * @author  György Kovács
 * @date    Jun 30, 2020
 * @brief   A library for LiquidCrystal display to scroll text in a specific position on the display.
 * 			Selectable animation mode
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) [2020] [György Kovács]
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 ******************************************************************************
 */
#ifndef LCDCUSTOMSCROLL_I2C_H_
#define LCDCUSTOMSCROLL_I2C_H_

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define SCMODE1 0x01
#define SCMODE2 0x02
#define SCMODE3 0x03
#define SCMODE4 0x04

class LcdCustomScroll_I2C {
public:

	LcdCustomScroll_I2C(LiquidCrystal_I2C &LCDdisplay);
	virtual ~LcdCustomScroll_I2C();

	void init(char* array, uint16_t scrollSpeed, uint8_t sor, uint8_t oszlopMin, uint8_t oszlopMax);
	void scrollMode(uint8_t mode);
	int8_t scrollText();

private:

	uint32_t gl_scrollDelay = 0;
	uint16_t gl_strHossz = 0;
	uint16_t gl_scrollSpeed = 0;
	int8_t gl_pozicio = 0;
	uint8_t gl_szabadhely = 0;
	uint8_t gl_sor = 0;
	uint8_t gl_oszlopMin = 0;
	uint8_t gl_mode = SCMODE1;
	bool gl_irany = true;

	LiquidCrystal_I2C* gl_lcd;
	char* gl_textArray;
};//end class

#endif /* LCDCUSTOMSCROLL_I2C_H_ */
