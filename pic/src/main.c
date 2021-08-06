#include <xc.h>

#include "../include/nibblenet.h"

//Global Variable Declaration
int motorDirection;
int continuousRotation;

int main(void)
{    
    motorDirection = 70;
    continuousRotation = 2;
    startNibbleNet2();
    
    return 0;
}
