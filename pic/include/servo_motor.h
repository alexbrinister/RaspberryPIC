/* 
 * @file servo_motor.h
 * @author Alex Brinister
 * @date February 13, 2018
 */

#ifndef __SERVO_MOTOR_H__
#define	__SERVO_MOTOR_H__

#include <xc.h>
#include <stdint.h>

/// Default sleep time that sets speed of servomotor (in microseconds).
static const unsigned long DEFAULT_SPEED_SLEEP_US   = 100000;

/// Duty cycle corresponding to 0 degrees.
static const unsigned DUTY_CYCLE_DEGREES_0          = 15;

// Duty cycle corresponding to 30 degrees.
static const unsigned DUTY_CYCLE_DEGREES_30         = 24;

// Duty cycle corresponding to 60 degrees.
static const unsigned DUTY_CYCLE_DEGREES_60         = 33;

// Duty cycle corresponding to 90 degrees.
static const unsigned DUTY_CYCLE_DEGREES_90         = 42;

// Duty cycle corresponding to 120 degrees.
static const unsigned DUTY_CYCLE_DEGREES_120        = 51;

// Duty cycle corresponding to 150 degrees.
static const unsigned DUTY_CYCLE_DEGREES_150        = 60;

// Duty cycle corresponding to 180 degrees.
static const unsigned DUTY_CYCLE_DEGREES_180        = 69;

/// Variable to keep track of duty cycle at all times.
static volatile unsigned duty_cycle_;

/* \func init_servo
 * \brief Initialize servo registers.
 */
void init_servo();

/* \func move_motor
 * \brief Set the servo to the specified duty cycle at the specified speed.
 * \param duty_cycle The target duty cycle.
 * \param speed The speed at which the motor will get to the duty cycle.
 */
void move_motor(uint16_t duty_cycle, float speed);

/* \func run_servo
 * \brief The main servo function that runs forever.
 */
void run_servo();

#endif	/* __SERVO_MOTOR_H__ */