/*----------------------------------------------------------------------------------------------
 * File Name:    icu.h                                                                         *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 22, 2023                                                                  *
 * Description:  header file for the ATmega32 ICU driver.                                      *
 *---------------------------------------------------------------------------------------------*/

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"
/************************************************************************************************
 *                             Static Configuration                                             *
 ************************************************************************************************/

/************************************************************************************************
 *                                User Type Define                                              *
 ************************************************************************************************/
typedef enum{
	NO_CLK,F_CPU_CLK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_Clock;

typedef enum{
	FALLING,RISING
}Icu_EdgeType;

typedef struct{
	Icu_Clock clock;
	Icu_EdgeType edge;
}Icu_ConfigType;

/************************************************************************************************
 *                              Function Prototypes                                             *
 ************************************************************************************************/
/*
 * Description: Function to initialize the ICU driver
 *  1. Set the required clock.
 *  2. Set the required edge detection.
 *  3. Enable the Input Capture Interrupt.
 *  4. Initialize Timer1 Registers
 */
void ICU_init(const Icu_ConfigType *Config_ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void (*a_ptr)(void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType edgetype);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);
#endif /* ICU_H_ */
