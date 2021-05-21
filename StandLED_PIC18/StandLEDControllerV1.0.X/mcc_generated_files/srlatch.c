/**
  SRLATCH Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    srlatch.c

  @Summary
    This is the generated driver implementation file for the SRLATCH driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for SRLATCH.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F25K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
 */

#include <xc.h>
#include "srlatch.h"

/**
  Section: SRLATCH APIs
 */

void SRLATCH_Initialize(void) {
    // SRNQEN disabled; SRCLK 1:4; SRLEN enabled; SRPR disabled; SRPS disabled; SRQEN disabled; 
    SRCON0 = 0x80;
    // SRRC1E disabled; SRSC2E disabled; SRRCKE disabled; SRRC2E disabled; SRSPE disabled; SRRPE disabled; SRSC1E disabled; SRSCKE disabled; 
    SRCON1 = 0x00;
}
/**
 End of File
 */
