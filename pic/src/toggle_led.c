/**
 * @file toggle_led.c
 * @author Alex Main
 * @brief Source file for LED toggle code.
 */

#include <xc.h>

#include "../include/toggle_led.h"

// Initialize the LED pin
void init_led()
{
    // Set the RC4 latch low
    IO_RC4_set_low();
    
    // Set RC4 to digital mode
    IO_RC4_set_digital_mode();
    
    // Set RC4 to digital output
    IO_RC4_set_digital_output();
    
    // Set the weak pull-up to 0
    IO_RC4_reset_pullup();
    
    // Set open-drain to push-pull
    IO_RC4_set_push_pull();
}

// Take in the address of a pin and write the state to it.
void toggle_led(unsigned int covered_state)
{
    IO_RC4_LAT = covered_state;
}
