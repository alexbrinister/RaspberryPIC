/**
 * @file ldr_read_pin.c
 * @author Alex Brinister
 * @date February 7, 2018, 12:06 AM
 */

#include <xc.h>
#include <stdint.h>

#include "../include/toggle_led.h"
#include "../include/ldr_read_pin.h"

void init_adc()
{
    /*
     * ADCON0 Bit Settings -> Register 23-1 (page 356)
     * 1. ADGO: Get a sample from the ADC (1).
     * 2. ADFRM0: MSB in ADRESH (1).
     * 3. ADCS: Clock is Fosc, divider is ADCLK (0).
     * 3. ADCONT: Continuous operation enabled (1).
     * 4. ADON: ADC enabled (1).
     */ 
    ADCON0bits.ADGO     = 1;
    ADCON0bits.ADFRM0   = 1;
    ADCON0bits.ADCS     = 0;
    ADCON0bits.ADCONT   = 1;
    ADCON0bits.ADON     = 1;
    
    /*
     * ADCON1 Bit Settings -> Register 23-2 (page 357)
     * 1. ADDSEN: Double sample disabled (0).
     * 2. ADGPOL: Guard ring outputs are start low during precharge (0).
     * 3. ADIPEN: Ignored (0).
     * 4. ADPPOL: Precharge shorted to Vss (0).
     */
    ADCON1bits.ADDSEN   = 0;
    ADCON1bits.ADGPOL   = 0;
    ADCON1bits.ADIPEN   = 0;
    ADCON1bits.ADPPOL   = 0;
    
    /*
     * ADCON2 Bit Settings -> Register 23-3 (page 358)
     * 1. ADMD: Set "Basic" operating mode (0).
     * 2. ADACLR: Accumulator clear disabled (0).
     * 3. ADCRS: Accumulator right shift ignored because of basic mode (0).
     * 4. ADPSIS: ADFLTR is transfered to ADPREV before conversion starts (0).
     */
    ADCON2bits.ADMD     = 0;
    ADCON2bits.ADACLR   = 0;
    ADCON2bits.ADCRS    = 0;
    ADCON2bits.ADPSIS   = 0;
    
    /*
     * ADCON3 Bit Settings -> Register 23-4 (page 359)
     * 1. ADTMD: Threshold interrupt is disabled (0).
     * 2. ADSOI: ADGO is cleared on interrupt (1).
     * 3. ADCALC: First derivative of single measurement (0).
     */
    ADCON3bits.ADTMD    = 0;
    ADCON3bits.ADSOI    = 1;
    ADCON3bits.ADCALC   = 0;
    
    /*
     * ADSTAT Bit Settings -> Register 23-5 (page 360)
     * 1. ADSTAT: ADC not converting (0).
     * 2. ADMATH: Bits have not changed (0).
     * 3. ADLTHR: ADERR >= ADLTH (0).
     * 4. ADUTHR: ADERR <= ADUTH (0).
     * 5. ADAOV: ADC accumulator and ADERR have not overflowed (0); 
     */
    ADSTATbits.ADSTAT   = 0;
    ADSTATbits.ADMATH   = 0;
    ADSTATbits.ADLTHR   = 0;
    ADSTATbits.ADUTHR   = 0;
    ADSTATbits.ADAOV    = 0;

    /*
     * ADCLK Bit Settings -> Register 23-6 (page 361)
     * 0x3f -> Value obtained from data sheet. This sets the ADC clock to be
     * 128th of the main oscillator value (i.e, Fosc/128).
     */
    ADCLK = 0x3F;
    
    /*
     * ADREF Bit Settings -> Register 23-7 (page 361)
     * 1. ADPREF: Positive ref is VDD.
     * 2. ADNREF: Negative reference is VSS
     */ 
    ADREFbits.ADNREF = 0;
    ADREFbits.ADPREF = 0;
    
    /*
     * ADPCH Bits Setting -> Register 23-8 (page 362)
     * 0b0011000 -> Obtained from data sheet Register 23-8 (page 362)
     * This sets the pin RB3 as an ADC pin.
     */ 
    ADPCH = 0xB;
    
    /*
     * ADCAP Bit Settings -> Register 23-11 (page 363)
     * This register sets the value for an additional sampling capacitor.
     * This is not used so is set to 0.
     */
    ADCAP = 0x00;
    
    /*
     * ADRPT Bit Settings -> Register 23-12 (page 364)
     * This register holds the count of the ADC being triggered. Set to 0 since
     * this is not applicable to Basic Mode.
     */
    ADRPT = 0x00;
        
    /*
     * ADSTPTL and ADSTPTH Bit Settings -> Registers 23-25 and 23-24 (page 369)
     * These registers set the set point for the ADC, which influences the
     * error calculation, depending on how ADCALC is set.
     */
    ADSTPTL = 0; 
    ADSTPTH = 0;
        
    /*
     * ADLTHL and ADLTHH Bit Settings -> Registers 23-29 and 23-28 (page 370)
     * These registers set the lower threshold for the ADC. They are divided 
     * into a lower and upper register.
     * Both are set to 0, as thresholds are not used. 
     */
    ADLTHL = 0; 
    ADLTHH = 0;
        
    /*
     * ADUTHL and ADUTHH Bit Settings -> Registers 23-31 and 23-30 (page 371) 
     * These registers set the upper threshold for the ADC. They are divided 
     * into a lower and upper register.
     * Both are set to 0, as thresholds are not used. 
     */
    ADUTHL = 0;
    ADUTHH = 0;
    
    /*
     * ADACT Bit Setting -> Register 23-32 (page 372)
     * 0x1D -> Obtained from Table 23-2 (page 343)
     * 
     * This register is responsible for setting the condition for ADC auto-
     * conversion. It is set to auto-convert on a read of the ADRESH register.
     */ 
    ADACT = 0x1D;

    // Enable global and peripheral interrupts
    //Interrupt on change configuration.
    //Enable all interrupts (GLOBAL)
    INTCONbits.GIE = 1;
    //Enable peripherals
    INTCONbits.PEIE = 1;
    //Interrupt on rising edge of pin
    INTCONbits.INTEDG = 1;
    //Enable interrupt on change 
    PIE0bits.IOCIE = 1;
    //Enable pin 4 for external interrupt on change for positive edge trigger.
    IOCAPbits.IOCAP4 = 1;
    //Clear interrupt on change flag.
    IOCAF = 0;
    
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
    
    // Disable ADCC interrupt.
    PIE1bits.ADIE = 0;
    
    // Initialize LED GPIO registers
    init_led();
    
    // Enable the ADC and start the conversion.
    ADC_enable();
    ADC_start_conv();
}

// Getter for the ADC value
adc_result_t get_ldr_value()
{
    shared_adc_value = ((adc_result_t)((ADRESH << 8) + ADRESL));
	return shared_adc_value;
}
