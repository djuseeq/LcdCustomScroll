# LcdCustomScroll
Scroll strings on the LCD display in a specific position

## API Reference
```C++
  //CONSTRUCTORS
//for LiquidCrystal library use:
LcdCustomScroll(LiquidCrystalObject);
//for LiquidCrystal_I2C library use:
LcdCustomScroll_I2C(LiquidCrystal_I2CObject);
/////////////////////////
init(charArray, ScrollSpeed, Row, startColumn, endColumn);
//charArray - pointer to the char array(C string) you want to scroll
//ScrollSpeed - unsigned int delay between text movements 
              //(The delay() function is not used so it does not block the program)
//Row , start and end column variables are position setting variables

scrollMode(mode);//SCMODE1, SCMODE2, SCMODE3, SCMODE4

//repeatedly call this function to get moving the text on the LCD
scrollText(); //returns int value,   0 - text moved
              //                     1 - end of the string has reached
              //                    -1 - beginning of the string has reached(available just in SCMODE1)
              //                    -2 - invalid mode has selected
```
