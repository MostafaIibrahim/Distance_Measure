/*----------------------------------------------------------------------------------------------
 * File Name:    icu.c                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 22, 2023                                                                  *
 * Description:  source file for the ATmega32 ICU driver.                                      *
 *---------------------------------------------------------------------------------------------*/
#include "icu.h"
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */

/************************************************************************************************
 *                                Set Global Definitions                                        *
 ************************************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/************************************************************************************************
 *                               ISR Implementation                                             *
 ************************************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}

/************************************************************************************************
 *                               Function Definitions                                           *
 ************************************************************************************************/
/*
 * Description: Function to initialize the ICU driver
 *  1. Set the required clock.
 *  2. Set the required edge detection.
 *  3. Enable the Input Capture Interrupt.
 *  4. Initialize Timer1 Registers
 */
void ICU_init(const Icu_ConfigType *Config_ptr)
{
	/* Configure ICP1/PD6 as i/p pin */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

	/* Timer1 always operates in Normal Mode */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xF8) | (Config_ptr->clock);

	/*
     * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_ptr->edge)<<6);

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	SET_BIT(TIMSK,TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void (*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType a_edgetype)
{
	/*
     * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | ((a_edgetype)<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1=0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	CLEAR_BIT(TIMSK,TICIE1);
}
