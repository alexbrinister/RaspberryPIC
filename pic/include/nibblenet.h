#ifndef __NIBBLENET_H__
#define	__NIBBLENET_H__

#include <xc.h>

/* user commands */
#define MSG_RESET 0x0 /* reset the sensor to initial state */
#define MSG_PING 0x1 /*check if the sensor is working properly */
#define MSG_GET 0x2 /* obtain the most recent ADC result */
#define MSG_TURN30 0x3 /* turn the servo motor blade  0 degrees */
#define MSG_TURN90 0x4 /* turn the servo motor blade 90 degrees */
#define MSG_TURN120 0x5 /* turn the servo motor blade 180 degrees */
#define MSG_CAM_SCAN_90 0x6 // Sets the camera rotation mode 0-90 
#define MSG_CAM_SCAN_180 0x7// Sets the camera rotation mode 0-180 
#define MSG_CAM_SCAN_0 0x8 // Sets the camera rotation mode Off,

/* Sensor Device Responses */
#define MSG_ACK 0xE /* acknowledgement to the commands */
#define MSG_NOTHING 0xF /* reserved */

#define INBIT_THREE PORTAbits.RA0
#define INBIT_TWO PORTAbits.RA1
#define INBIT_ONE PORTAbits.RA2
#define INBIT_ZERO PORTAbits.RA3

#define STROBE_PIN PORTAbits.RA4

#define OUTBIT_THREE LATAbits.LATA7
#define OUTBIT_TWO LATAbits.LATA6
#define OUTBIT_ONE LATCbits.LATC0
#define OUTBIT_ZERO LATCbits.LATC1

// check for message from Galileo and return as decimal value
int receive_msg();

//set output pins for ACK_MSG
void sendACK();

//clear output pins
void clrOutput();

void startNibbleNet2(void);
void interrupt isr();

#endif /* __NIBBLENET_H__ */