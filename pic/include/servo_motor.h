/* 
 * @file servo_motor.h
 * @author Alexander Main
 * @date February 13, 2018
 */

#ifndef __SERVO_MOTOR_H__
#define	__SERVO_MOTOR_H__

#include <xc.h>
#include <stdint.h>

//GLOBAL
extern int motorDirection;
extern int continuousRotation;

static const int DUTY_CYCLE_DEGREES_0   = 15;
static const int DUTY_CYCLE_DEGREES_30  = 24;
static const int DUTY_CYCLE_DEGREES_60  = 33;
static const int DUTY_CYCLE_DEGREES_90  = 42;
static const int DUTY_CYCLE_DEGREES_120 = 51;
static const int DUTY_CYCLE_DEGREES_150 = 60;
static const int DUTY_CYCLE_DEGREES_180 = 70;

void init_servo();
void move_motor(uint16_t duty_cycle, float speed);
void run_servo();

#endif	/* __SERVO_MOTOR_H__ */

