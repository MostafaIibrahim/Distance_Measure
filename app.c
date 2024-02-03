/*----------------------------------------------------------------------------------------------
 * File Name:    app.c                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 22, 2023                                                                  *
 * Description:  source file for Application ultrasonic project implementation.                *
 *---------------------------------------------------------------------------------------------*/
#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>


int main()
{
	uint16 distance ;
	LCD_init();
	ULTRASONIC_init();

	SREG |= (1<<7);

	LCD_displayString("Distance=    cm");
	while(1)
	{
		distance = ULTRASONIC_readDistance();
		if(distance <100)
		{
		LCD_moveCursor(0,10);
		LCD_intgerToString(distance);
		LCD_displayCharacter(' ');
		}
		else
		{
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance);
		}
	}
}

