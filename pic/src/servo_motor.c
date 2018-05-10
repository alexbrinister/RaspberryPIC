#include <xc.h>
#include <stdint.h>

#include "../include/config.h"
#include "../include/servo_motor.h"

/* 
 * Initialization function for servomotor
 * Initializes the servo to 7.5% duty cycle PWM signal. 
 * This is about 90 degrees.
 */ 
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
    
    // Select Timer 2.
    CCPTMRS1bits.P6TSEL = 1;
    
    // Configure Timer 2 clock source.
    // Timer 2 set for FOSC/4. (Might not need this!)
    T2CLKCONbits.CS = 0x1;
    
    // Set Timer 2 period to maximum
    // This is required for best resolution.
    T2PR = 0xFF;
    
    // Clear Timer 2 interrupt flag.
    PIR4bits.TMR2IF = 0;

    /* 
     * Timer 2 configuration
     * 1. Output post-scaler set to 1:1.
     * 2. Clock pre-scaler set to 1:128.
     * 3. Turn the timer on.
     */ 
    T2CONbits.OUTPS = 0x0;
    T2CONbits.CKPS = 0b111;
    T2CONbits.ON = 1;    
}

// Move the motor to a certain angle as dictated by the duty cycle
// TODO: Implement a speed control for this
void move_motor(uint16_t duty_cycle, float speed)
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

void run_servo()
{
    // Initialize oscillator and servo.
    init_osc();
    init_servo();

    while (1)
    {
        move_motor(DUTY_CYCLE_DEGREES_0, 0);
        __delay_us(1000000);
        move_motor(DUTY_CYCLE_DEGREES_30, 0);
        __delay_us(1000000);
        move_motor(DUTY_CYCLE_DEGREES_60, 0);
        __delay_us(1000000);
        move_motor(DUTY_CYCLE_DEGREES_90, 0);
        __delay_us(1000000);
        move_motor(DUTY_CYCLE_DEGREES_120, 0);
        __delay_us(1000000);
        move_motor(DUTY_CYCLE_DEGREES_150, 0);
        __delay_us(1000000);
        move_motor(DUTY_CYCLE_DEGREES_180, 0);
        __delay_us(1000000);

    }
}