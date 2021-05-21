
#ifndef MCC_H
#define	MCC_H
#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "tmr0.h"
#include "eusart1.h"
#include "adc.h"
#include "tmr2.h"
#include "epwm.h"

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */
void SYSTEM_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 * @Example
    OSCILLATOR_Initialize(void);
 */
void OSCILLATOR_Initialize(void);


#endif	/* MCC_H */
/**
 End of File
 */