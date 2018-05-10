#include <xc.h>

#include "../include/servo_motor.h"

//Global Variable Declaration
int motorDirection;
int continuousRotation;

int main(void)
{    
    motorDirection = 70;
    continuousRotation = 2;
    run_servo();
    
    return 0;
}
