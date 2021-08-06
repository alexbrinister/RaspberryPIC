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

static const int DUTY_CYCLE_DEGREES_0   = 20;
static const int DUTY_CYCLE_DEGREES_30  = 28;
static const int DUTY_CYCLE_DEGREES_90  = 45;
static const int DUTY_CYCLE_DEGREES_120 = 54;
static const int DUTY_CYCLE_DEGREES_180 = 70;

void init_servo();
void move_motor(uint16_t duty_cycle);

#endif	/* __SERVO_MOTOR_H__ */

