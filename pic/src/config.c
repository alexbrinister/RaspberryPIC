/**
 * @file config.c
 * @author Alex Brinister
 * @date February 25, 2018
 */

#include <xc.h>
#include "../include/config.h"

void init_osc()
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 4_MHz; 
    OSCFRQ = 0x02;
    // HFTUN 32; 
    OSCTUNE = 0x20;
}
