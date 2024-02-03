/*----------------------------------------------------------------------------------------------
 * File Name:    ultrasonic.h                                                                  *
 * Author:       Mustafa Ibrahim                                                               *
 * Data Created: Apr 22, 2023                                                                  *
 * Description:  header file for the Ultrasonic  HC_SR04 driver.                               *
 *---------------------------------------------------------------------------------------------*/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include"std_types.h"

/**********************************************************************************************
 *                                 Static configuration                                       *
 **********************************************************************************************/
#define ULTRASONIC_TRIGGER_PORT_ID        PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID         PIN5_ID

#define ULTRASONIC_ECHO_PORT_ID           PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID            PIN6_ID

/**********************************************************************************************
 *                                 Functions Prototypes                                       *
 **********************************************************************************************/

/*
 * Description:
 *  Initialize the ICU driver as required.
 *  Setup the ICU call back function.
 *  Setup the direction for the trigger pin as output pin through the GPIO driver.
 * Inputs: None.
 * Return: None.
 */
void ULTRASONIC_init(void);

/*
 * Description:
 *  Send the Trigger pulse to the ultrasonic.
 * Inputs: None.
 * Return: None.
 */
void ULTRASONIC_trigger(void);

/*
 * Description:
 *  Send the trigger pulse by using Ultrasonic_trigger function.
 *  Start the measurements by the ICU from this moment.
 * Inputs: None.
 * Return: The measured distance in Centimeter.
 */
uint16 ULTRASONIC_readDistance(void);

/*
 * Description:
 *  This is the call back function called by the ICU driver.
 *  This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 * Inputs: None.
 * Return: None.
 */
void ULTRASONIC_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
