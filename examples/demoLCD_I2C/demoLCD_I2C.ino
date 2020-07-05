/*--------------------------------------------------------------------------------
 *    Author: György Kovács                                                       |
 *    Created: 05 Jul 2020                                                        |
 *    Description: Create scrolling text elements on I2C character LCD display    |
 *                 with delay when reach the end of the string                    |
 *--------------------------------------------------------------------------------
 */
#include <Arduino.h>

#include <LiquidCrystal_I2C.h> //I2C LCD
#include <LcdCustomScroll_I2C.h>

//First, instantiate the LCD object (change values as needed)
LiquidCrystal_I2C lcd(0x27,20,4);// I2C address, columns, rows

//Second, instantiate the scrolling text object(s)
LcdCustomScroll_I2C scroll1(lcd);
LcdCustomScroll_I2C scroll2(lcd);
LcdCustomScroll_I2C scroll3(lcd);
LcdCustomScroll_I2C scroll4(lcd);

char longText1[] = "Let's see how this scrolling text works !";
char longText2[] = "The quick brown fox jumps over the lazy dog";
char longText3[] = "This is the third row and this scrolling text is awesome ! ";
char longText4[] = "We do nothing in the fourth line :)";

unsigned long txtTimer1 = 0xFFFF00;
unsigned long txtTimer2 = 0xFFFF00;
unsigned long txtTimer3 = 0xFFFF00;
unsigned long txtTimer4 = 0xFFFF00;

unsigned long timerCnt = 0;

byte counter = 0;


    void setup() {
    	lcd.init();
    	lcd.backlight();
    	
    	//First row
    	scroll1.init(longText1, 300, 0, 9, 16);//Scroll speed(ms), row, from column, to column
    	scroll1.scrollMode(SCMODE1);//Scroll modes: SCMODE1, SCMODE2, SCMODE3, SCMODE4

    	//Second row
    	scroll2.init(longText2, 500, 1, 3, 15);
    	scroll2.scrollMode(SCMODE2);

    	//Third row
    	scroll3.init(longText3, 500, 2, 0, 20);
    	scroll3.scrollMode(SCMODE3);

    	//Fourth row
    	scroll4.init(longText4, 200, 3, 10, 19);
    	scroll4.scrollMode(SCMODE4);

    }//end setup

    void loop() {
		//Print counter to LCD
    	if(millis() - timerCnt >= 1000){
    		char shortText[10];
    		timerCnt = millis();
    		if(!counter){
    			snprintf_P(shortText, sizeof(shortText), PSTR("        "));
        		lcd.setCursor(0,0);
        		lcd.print(shortText);
    		}
    		snprintf_P(shortText, sizeof(shortText), PSTR("Cnt :%i"),counter);
    		lcd.setCursor(0,0);
    		lcd.print(shortText);
    		counter++;
    	}//end if print counter

    	if(millis() - txtTimer1 >= 1000 && scroll1.scrollText()){
    		txtTimer1 = millis();
    	}

    	if(millis() - txtTimer2 >= 1000 && scroll2.scrollText()){
        		txtTimer2 = millis();
        	}

    	if(millis() - txtTimer3 >= 3000 && scroll3.scrollText()){
        		txtTimer3 = millis();
        	}

    	if(millis() - txtTimer4 >= 2000 && scroll4.scrollText()){
        		txtTimer4 = millis();
        	}
    }//end main loop
