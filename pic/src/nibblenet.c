/*
 * File:   nibblenet.c
 * Author: cedmonds
 */

#include <xc.h>
#include <stdint.h>

#include "../include/config.h"
#include "../include/ldr_read_pin.h"
#include "../include/servo_motor.h"
#include "../include/nibblenet.h"

// check for message from Galileo and return as decimal value

int receive_msg() {
    int rec = 0;

    rec += 1 * INBIT_ZERO;
    rec += 2 * INBIT_ONE;
    rec += 4 * INBIT_TWO;
    rec += 8 * INBIT_THREE;

    return rec;
}//END receive_msg

//clear output pins

void clrOutput() {
    OUTBIT_THREE = 0; //set bit according to mod cell
    OUTBIT_TWO = 0; //set bit according to mod cell
    OUTBIT_ONE = 0; //set bit according to mod cell
    OUTBIT_ZERO = 0; //set bit according to mod cell
}// END clrOutput

//set output pins for ACK_MSG

void sendACK() {
    OUTBIT_THREE = 1; //set bit according to mod cell
    OUTBIT_TWO = 1; //set bit according to mod cell
    OUTBIT_ONE = 1; //set bit according to mod cell
    OUTBIT_ZERO = 0; //set bit according to mod cell

    while (!STROBE_PIN); // wait for strobe
    while (STROBE_PIN); // falling edge
    clrOutput(); //clear read message
}// END sendACK

void startNibbleNet2(void) {
    uint16_t data = 0, i;
    // Initialize pins, ADCC, and oscillator.
    // Also, set the configuration bits for the PIC16F18857 chip.
    init_osc();
    init_servo();
    init_adc();

    //set reg A for RX and pins RA6 and RA7 for TX
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 0;

    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA1 = 0;

    TRISAbits.TRISA2 = 1;
    ANSELAbits.ANSA2 = 0;

    TRISAbits.TRISA3 = 1;
    ANSELAbits.ANSA3 = 0;

    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 0;

    //set reg C pins for TX
    TRISAbits.TRISA7 = 0;
    ANSELAbits.ANSA7 = 0;

    TRISAbits.TRISA6 = 0;
    ANSELAbits.ANSA6 = 0;

    TRISCbits.TRISC0 = 0;
    ANSELCbits.ANSC0 = 0;

    TRISCbits.TRISC1 = 0;
    ANSELCbits.ANSC1 = 0;

    clrOutput();


    //New code that will loop unless interrupted by strobe pin.
    int delayCount = 0;
    int total_ms = 1000;
    int stop = 0;

    while (1) {//do these instructions forever

        if ((continuousRotation == 2)&&(delayCount == (total_ms))) {
            move_motor(motorDirection);
        } else if (continuousRotation == 1) {
            TRISAbits.TRISA5 = 0;
            move_motor(motorDirection);
            __delay_ms(1000);
            delayCount = 0;
            continuousRotation = 0;
            TRISAbits.TRISA5 = 1;
        }

        if ((continuousRotation == 2)&&(delayCount < 1)) {
            move_motor(DUTY_CYCLE_DEGREES_0);
        }

        if (continuousRotation == 2) {
            TRISAbits.TRISA5 = 0;
            if (delayCount++ > total_ms * 2) {
                delayCount = 0;
            }
            __delay_ms(1);
        }

    }//END while

}

void interrupt isr(void) {
    //ISR GLBOAL PREVENTS ISR FROM BEING CALLED DURING OPERATION
    INTCONbits.GIE = 0;

    uint16_t data = 0, i;


    while (!STROBE_PIN); // wait for strobe high
    if (receive_msg() == MSG_PING) {//check if the sensor is working properly
        while (STROBE_PIN); // wait for strobe low
        sendACK(); //send acknowledgment
    } else if (receive_msg() == MSG_GET) {//obtain the most recent ADC result
        data = get_ldr_value(); //get ADC
        while (STROBE_PIN); // wait for strobe low

        //set output pins in nibbles
        uint16_t compr = 2048;

        // Loop through 3 times, each time writing to the message
        // bits and waiting for the falling edge of the strobe.
        //
        // The funky syntax is making a logical decision based on the result
        // of the AND between the comparison value and the data value. This
        // is a bitwise AND that results in a 1 or a 0 in the bit location
        // coincident with the comparison value. If there is a value of 1
        // at any bit in the result of the AND, the value of the pin is 1.
        // Otherwise, the pin is set to 0.
        for (i = 0; i < 3; i++) {
            OUTBIT_THREE = compr & data ? 1 : 0;
            compr >>= 1;
            OUTBIT_TWO = compr & data ? 1 : 0;
            compr >>= 1;
            OUTBIT_ONE = compr & data ? 1 : 0;
            compr >>= 1;
            OUTBIT_ZERO = compr & data ? 1 : 0;
            compr >>= 1;

            while (!STROBE_PIN); // wait for strobe
            while (STROBE_PIN); // falling edge
        }
        sendACK(); //set pins for ACK

    } else if (receive_msg() == MSG_TURN30) {//turn the servo motor blade 0 degrees
        while (STROBE_PIN); // wait for strobe low
        continuousRotation = 1;
        motorDirection = DUTY_CYCLE_DEGREES_30; //set PWM to 0 degrees
        sendACK(); //set pins for ACK
    } else if (receive_msg() == MSG_TURN90) {//turn the servo motor blade 90 degrees
        while (STROBE_PIN); // wait for strobe low
        continuousRotation = 1;
        motorDirection = DUTY_CYCLE_DEGREES_90; //set PWM to 90 degrees
        sendACK(); //set pins for ACK
    } else if (receive_msg() == MSG_TURN120) {//turn the servo motor blade 180 degrees
        while (STROBE_PIN); // wait for strobe low
        continuousRotation = 1;
        motorDirection = DUTY_CYCLE_DEGREES_120; //set PWM to 180 degrees
        sendACK(); //set pins for ACK
    } else if (receive_msg() == MSG_CAM_SCAN_0) {//turn the servo motor blade 90 degrees
        while (STROBE_PIN); // wait for strobe low
        sendACK(); //set pins for ACK
        TRISAbits.TRISA5 = 1;
        continuousRotation = 0;
    } else if (receive_msg() == MSG_CAM_SCAN_90) {//turn the servo motor blade 90 degrees
        while (STROBE_PIN); // wait for strobe low
        sendACK(); //set pins for ACK
        continuousRotation = 2;
        motorDirection = DUTY_CYCLE_DEGREES_90;
    }else if (receive_msg() == MSG_CAM_SCAN_180) {//turn the servo motor blade 90 degrees
        while (STROBE_PIN); // wait for strobe low
        sendACK(); //set pins for ACK
        continuousRotation = 2;
        motorDirection = DUTY_CYCLE_DEGREES_180;
    }else if(receive_msg() == MSG_RESET){
        while (STROBE_PIN); // wait for strobe low
        // reset the sensor to initial
        clrOutput();
    }


    //ISR GLBOAL PREVENTS ISR FROM BEING CALLED DURING OPERATION
    //Clear Interrupt Flag.
    IOCAF = 0;
    //All future interrupts.
    INTCONbits.GIE = 1;
}

