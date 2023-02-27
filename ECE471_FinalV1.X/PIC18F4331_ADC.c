#include "PIC18F4331_ADC.h"

typedef union{
    uint16_t ADC_Raw;
    struct{
        uint8_t result_low;
        uint8_t result_high;
    }ADCRES_Members;
}ADC_Result;

static ADC_Result ADC;

static void ADC_start(void)
{
    ADCON0bits.ADON = 1;
    ADCON0bits.GODONE = 1;
}

static void ADC_stop(void)
{
    ADCON0bits.ADON = 0;
}

void ADC_init(void)
{
    //stop ADC to begin with
    ADC_stop();
    
    //Setting VREF +/- to AVDD/AVSS
    ADCON1bits.VCFG = 0;
    
    //setting ADC Channel to AN0
    ADCHSbits.GASEL0 = 0;
    ADCHSbits.GASEL1 = 0;
    
    //Single Shot loop (page 253: 20.1.1)
    ADCON0bits.ACONV = 0;
    
    //Conversion Clock Select to FOSC/2
    ADCON2bits.ADCS = 0;
    
    //Right justified
    ADCON2bits.ADFM = 1;
    
    //No delay in A/D Acquisition Time
    ADCON2bits.ACQT = 0;

    //Input function on AN0 and disable digital input
    ANSEL0bits.ANS0 = 1;
      
}

static uint8_t ADC_in_progress(void)
{
    //returns the status of the conversion
    //0 for completed, 1 for in-progress
    return (ADCON0bits.GODONE);
}

uint16_t ADC_Read(void)
{
    ADC_start();
    
    //wait until GO/DONE bit goes to 0
    while(ADC_in_progress()); 
    
    //read results
    ADC.ADCRES_Members.result_high = ADRESH;
    ADC.ADCRES_Members.result_low = ADRESL;
    
   //return results
    return (ADC.ADC_Raw);
}
