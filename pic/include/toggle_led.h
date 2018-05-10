/** 
 * @file toggle_led.h   
 * @author Alex Main
 * @brief Header for toggling LED function based on LDR input
 */

#ifndef __TOGGLE_LED_H__
#define	__TOGGLE_LED_H__

#include <xc.h>

#define HIGH    1
#define LOW     0

// Get/set IO_RC4 aliases
// From MCC
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODCC4
#define IO_RC4_ANS                  ANSELCbits.ANSC4
#define IO_RC4_set_high()           IO_RC4_LAT = HIGH;
#define IO_RC4_set_low()            IO_RC4_LAT = LOW;
#define IO_RC4_toggle()             IO_RC4_LAT ~= IO_RC4_LAT;
#define IO_RC4_get_value()          IO_RC4_PORT
#define IO_RC4_set_digital_input()  IO_RC4_TRIS = HIGH;
#define IO_RC4_set_digital_output() IO_RC4_TRIS = LOW;
#define IO_RC4_set_pullup()         IO_RC4_WPU = HIGH;
#define IO_RC4_reset_pullup()       IO_RC4_WPU = LOW;
#define IO_RC4_set_push_pull()      IO_RC4_OD = LOW;
#define IO_RC4_set_open_drain()     IO_RC4_OD = HIGH;
#define IO_RC4_set_analog_mode()    IO_RC4_ANS = HIGH;
#define IO_RC4_set_digital_mode()   IO_RC4_ANS = LOW;

/**
 * @brief Set up the LED GPIO pin
 * 
 * @details Initializes pin A0 (RA0) by setting the latch to LOW, tri-state to 
 * LOW for output, analog select to HIGH, and output drain mode to standard
 * push-pull.
 */
void init_led();

/**
 * @brief Toggle LED if the LDR is covered.
 * 
 * @details The LED is if the LDR is in the "covered" state, which is determined
 * by whether the LDR voltage reading surpasses a threshold of COVERED_VALUE.
 * 
 * @param covered_state A boolean (0 or 1) indicating the state of the LDR.
 */
void toggle_led(unsigned int covered_state);

#endif	/* __TOGGLE_LED_H__ */