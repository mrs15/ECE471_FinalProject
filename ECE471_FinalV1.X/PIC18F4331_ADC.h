  
#ifndef PIC18F4331_ADC_H
#define	PIC18F4331_ADC_H

/*Author: Muhammad Rafay Shams*/

#include <xc.h> // include processor files - each processor file is guarded. 
#include "SystemConfiguration.h"

void ADC_init(void);
uint16_t ADC_Read(void);


#endif	/* XC_HEADER_TEMPLATE_H */

