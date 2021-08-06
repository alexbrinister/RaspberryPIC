#include <xc.h>
#include <stdint.h>

#include "../include/config.h"
#include "../include/servo_motor.h"
#include "../include/nibblenet.h"

// Initialization function for servomotor
// Initializes the servo to 7.5% duty cycle PWM signal.
void init_servo()
{
    /* GPIO pin Config for RA5 */
    // Set as digital pin and enable output driver. 
    ANSELAbits.ANSA5 = 0;
    TRISAbits.TRISA5 = 0;
		
    // Map PWM6OUT to GPIO pin RA5.
	// Value from Table 13-3 on page 246 of PIC16F18857 Datasheet.
    RA5PPS = 0x0E;

    /* PWM Config
	 * 1. Enable the PWM6 module.
     * 2. Set output level to low when bit is read.
     * 3. Set polarity to active high.
     */
	PWM6CONbits.PWM6EN = 1;
    PWM6CONbits.PWM6OUT = 0;
    PWM6CONbits.PWM6POL = 0;
    
    // Write upper 6 bits to PWMxDCH register ~7.5% duty cycle.
    PWM6DCH = (DUTY_CYCLE_DEGREES_90 & 0x03FC) >> 2;
    // Write lower 2 bits to the upper 2 bits of PWNxDCL ~7.5% duty cycle.
    PWM6DCL = (DUTY_CYCLE_DEGREES_90 & 0x0003) << 6;
    
    //Select Timer.
    CCPTMRS1bits.P6TSEL = 1;
    
    // Configure timer 2 clock.
    // Timer 2 set for FOSC/4. (Might not need this!)
    T2CLKCONbits.CS = 0x1;
    
    // Set for ~20ms period.
    // Obtained using Equation 19-1 from the PIC16F18857 datasheet (page 286).
    T2PR = 0xFF;//155;
    
    PIR4bits.TMR2IF = 0;//Clear timer 2 interrupt flag. 

    T2CONbits.OUTPS = 0x0;
    T2CONbits.CKPS = 0b111;
    T2CONbits.ON = 1;    
}

void move_motor(uint16_t duty_cycle)
{
    uint16_t duty_cycle_ = 0;
    
    // Limit the duty cycle to the duty cycle range from 0 to 180 degrees.
    if(duty_cycle >= DUTY_CYCLE_DEGREES_180)
        duty_cycle_ = DUTY_CYCLE_DEGREES_180;
    else if(duty_cycle <= DUTY_CYCLE_DEGREES_0)
        duty_cycle_ = DUTY_CYCLE_DEGREES_0;
    else
        duty_cycle_ = duty_cycle;
    
    // Write upper 6 bits to PWMxDCH register ~ 5% duty cycle.
    PWM6DCH = (duty_cycle_ & 0x03FC) >> 2;
    // Write lower 2 bits to the upper 2 bits of PWNxDCL ~5% duty cycle.
    PWM6DCL = (duty_cycle_ & 0x0003) << 6;
}