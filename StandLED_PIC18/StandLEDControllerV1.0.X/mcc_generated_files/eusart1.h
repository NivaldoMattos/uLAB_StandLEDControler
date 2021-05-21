
#ifndef _EUSART1_H
#define _EUSART1_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
//#include <app.h>


#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      Section: Macro Declarations
     */

#define EUSART1_DataReady  (eusart1RxCount)

    /**
      Section: Data Type Definitions
     */

    /**
     Section: Global variables
     */
    extern volatile uint8_t eusart1TxBufferRemaining;
    extern volatile uint8_t eusart1RxCount;
    
    //extern volatile uint8_t TX_OK=0;
    
    
    /**
      Section: EUSART1 APIs
     */

    /**
      @Summary
        Initialization routine that takes inputs from the EUSART1 GUI.

      @Description
        This routine initializes the EUSART1 driver.
        This routine must be called before any other EUSART1 routine is called.

      @Preconditions
        None

      @Param
        None

      @Returns
        None

      @Comment

      @Example
     */
    void EUSART1_Initialize(void);

    /**
      @Summary
        Read a byte of data from the EUSART1.

      @Description
        This routine reads a byte of data from the EUSART1.

      @Preconditions
        EUSART1_Initialize() function should have been called
        before calling this function. The transfer status should be checked to see
        if the receiver is not empty before calling this function.
	
        EUSART1_DataReady is a macro which checks if any byte is received.
        Call this macro before using this function.

      @Param
        None

      @Returns
        A data byte received by the driver.
	
      @Example
        <code>
                void main(void) {
                                    // initialize the device
                                    SYSTEM_Initialize();
                                    uint8_t data;
								
                                    // Enable the Global Interrupts
                                    INTERRUPT_GlobalInterruptEnable();
								
                                    // Enable the Peripheral Interrupts
                                    INTERRUPT_PeripheralInterruptEnable();
								
                                    printf("\t\tTEST CODE\n\r");		//Enable redirect STDIO to USART before using printf statements
                                    printf("\t\t---- ----\n\r");
                                    printf("\t\tECHO TEST\n\r");
                                    printf("\t\t---- ----\n\n\r");
                                    printf("Enter any string: ");
                                    do{
                                    data = EUSART1_Read();		// Read data received
                                    EUSART_Write(data);			// Echo back the data received
                                    }while(!EUSART1_DataReady);		//check if any data is received
								
                                }
        </code>
     */
    uint8_t EUSART1_Read(void);

    /**
     @Summary
       Writes a byte of data to the EUSART1.

     @Description
       This routine writes a byte of data to the EUSART1.

     @Preconditions
       EUSART1_Initialize() function should have been called
       before calling this function. The transfer status should be checked to see
       if transmitter is not busy before calling this function.

     @Param
       txData  - Data byte to write to the EUSART1

     @Returns
       None
  
     @Example
         <code>
             Refer to EUSART1_Read() for an example	
         </code>
     */
    void EUSART1_Write(uint8_t txData);

    /**
      @Summary
        Maintains the driver's transmitter state machine and implements its ISR.

      @Description
        This routine is used to maintain the driver's internal transmitter state
        machine.This interrupt service routine is called when the state of the
        transmitter needs to be maintained in a non polled manner.

      @Preconditions
        EUSART1_Initialize() function should have been called
        for the ISR to execute correctly.

      @Param
        None

      @Returns
        None
     */
    void EUSART1_Transmit_ISR(void);

    /**
      @Summary
        Maintains the driver's receiver state machine and implements its ISR

      @Description
        This routine is used to maintain the driver's internal receiver state
        machine.This interrupt service routine is called when the state of the
        receiver needs to be maintained in a non polled manner.

      @Preconditions
        EUSART1_Initialize() function should have been called
        for the ISR to execute correctly.

      @Param
        None

      @Returns
        None
     */
    void EUSART1_Receive_ISR(void);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  // _EUSART1_H
/**
 End of File
 */
