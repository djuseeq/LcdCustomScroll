/**
 ******************************************************************************
 * @file    LcdCustomScroll.cpp
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
#include "LcdCustomScroll.h"

LcdCustomScroll::LcdCustomScroll(LiquidCrystal &LCDdisplay) { // @suppress("Class members should be properly initialized")
	gl_lcd = &LCDdisplay;
}

LcdCustomScroll::~LcdCustomScroll() {
	// TODO Auto-generated destructor stub
}

void LcdCustomScroll::init(char* array, uint16_t scrollSpeed, uint8_t sor, uint8_t oszlopMin, uint8_t oszlopMax){
	gl_pozicio = 0;
	gl_irany = true;
	gl_textArray = array;
	gl_scrollSpeed = scrollSpeed;
	gl_sor = sor;
	gl_oszlopMin = oszlopMin;
	gl_szabadhely = oszlopMax - oszlopMin;
	gl_strHossz = strlen(gl_textArray);
}

void LcdCustomScroll::scrollMode(uint8_t mode){
	gl_mode = mode;
}

int8_t LcdCustomScroll::scrollText(){
	int8_t answer = 0;
	int8_t b = 0;
	if(millis() - gl_scrollDelay >= gl_scrollSpeed){
		//Print text to LCD
		for(uint8_t a = 0; a < gl_szabadhely; a++ ){
			if(!gl_textArray[a + gl_pozicio] && (gl_mode == SCMODE1 || gl_mode == SCMODE2)){
				break;// in this case stop printing to the LCD
			} else if ((!gl_textArray[a + gl_pozicio + b]) && gl_mode == SCMODE3){
				b = (0 - a) - gl_pozicio;// in case of MODE3, use the help variable to jump to the beginning of the string
			}
			// set cursor to the free allocated place
			gl_lcd->setCursor(gl_oszlopMin + a, gl_sor);
			if ((a + (uint8_t)gl_pozicio >= gl_strHossz) && gl_mode == SCMODE4){
				gl_lcd->write(' ');
			} else {
				gl_lcd->write(gl_textArray[(a + gl_pozicio) + b]);
			}
		}//end for loop

		if(gl_irany){
			gl_pozicio++;
		} else {
			gl_pozicio--;
		}//end if irany

		//Check reached the end
		switch (gl_mode) {
			case SCMODE1:
				if(gl_irany){
					//string shorter than allocated space on LCD or position reached the end of the string
					if(gl_strHossz < gl_szabadhely || (!gl_textArray[(gl_szabadhely + gl_pozicio) - 1])){
						gl_pozicio--;
						gl_irany = false;
						answer = 1;
					}//end if
				} else {
					if(gl_pozicio < 0){
						gl_pozicio = 0;
						gl_irany = true;
						answer = -1;
					}//end if
				}//end if irany
				break;

			case SCMODE2://string shorter than allocated space on LCD or position reached the end of the string
				if(gl_strHossz < gl_szabadhely || (!gl_textArray[(gl_szabadhely + gl_pozicio) - 1])){
					gl_pozicio = 0;
					answer = 1;
				} //end if
				break;
			case SCMODE3:
				if((uint8_t)gl_pozicio >  gl_strHossz){
					gl_pozicio = 0;
					answer = 1;
				} //end if
				break;
			case SCMODE4:
				if((uint8_t)gl_pozicio >  gl_strHossz){
					gl_pozicio = 0;
					answer = 1;
				} //end if
				break;
			default: // don't move the text, return error (-2)
				gl_pozicio = 0;
				gl_irany = !gl_irany;
				answer = -2;
				break;
		}
			gl_scrollDelay = millis();
	}//end if millis

	return answer;
}
