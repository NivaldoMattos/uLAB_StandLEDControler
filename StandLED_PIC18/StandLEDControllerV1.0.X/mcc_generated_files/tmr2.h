
#ifndef _TMR2_H
#define _TMR2_H

/**
  Section: Included Files
 */

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif


    /**
      Section: Macro Declarations
     */

    /**
      Section: TMR2 APIs
     */

    /**
      @Summary
        Initializes the TMR2 module.

      @Description
        This function initializes the TMR2 Registers.
        This function must be called before any other TMR2 function is called.

      @Preconditions
        None

      @Param
        None

      @Returns
        None

      @Comment
    

      @Example
        <code>
        main()
        {
            // Initialize TMR2 module
            TMR2_Initialize();

            // Do something else...
        }
        </code>
     */
    void TMR2_Initialize(void);

    /**
      @Summary
        This function starts the TMR2.

      @Description
        This function starts the TMR2 operation.
        This function must be called after the initialization of TMR2.

      @Preconditions
        Initialize  the TMR2 before calling this function.

      @Param
        None

      @Returns
        None

      @Example
        <code>
        // Initialize TMR2 module

        // Start TMR2
        TMR2_StartTimer();

        // Do something else...
        </code>
     */
    void TMR2_StartTimer(void);

    /**
      @Summary
        This function stops the TMR2.

      @Description
        This function stops the TMR2 operation.
        This function must be called after the start of TMR2.

      @Preconditions
        Initialize  the TMR2 before calling this function.

      @Param
        None

      @Returns
        None

      @Example
        <code>
        // Initialize TMR2 module

        // Start TMR2
        TMR2_StartTimer();

        // Do something else...

        // Stop TMR2;
        TMR2_StopTimer();
        </code>
     */
    void TMR2_StopTimer(void);

    /**
      @Summary
        Reads the TMR2 register.

      @Description
        This function reads the TMR2 register value and return it.

      @Preconditions
        Initialize  the TMR2 before calling this function.

      @Param
        None

      @Returns
        This function returns the current value of TMR2 register.

      @Example
        <code>
        // Initialize TMR2 module

        // Start TMR2
        TMR2_StartTimer();

        // Read the current value of TMR2
        if(0 == TMR2_ReadTimer())
        {
            // Do something else...

            // Reload the TMR value
            TMR2_Reload();
        }
        </code>
     */
    uint8_t TMR2_ReadTimer(void);

    /**
      @Summary
        Writes the TMR2 register.

      @Description
        This function writes the TMR2 register.
        This function must be called after the initialization of TMR2.

      @Preconditions
        Initialize  the TMR2 before calling this function.

      @Param
        timerVal - Value to write into TMR2 register.

      @Returns
        None

      @Example
        <code>
        #define PERIOD 0x80
        #define ZERO   0x00

        while(1)
        {
            // Read the TMR2 register
            if(ZERO == TMR2_ReadTimer())
            {
                // Do something else...

                // Write the TMR2 register
                TMR2_WriteTimer(PERIOD);
            }

            // Do something else...
        }
        </code>
     */
    void TMR2_WriteTimer(uint8_t timerVal);

    /**
      @Summary
        Load value to Period Register.

      @Description
        This function writes the value to PR2 register.
        This function must be called after the initialization of TMR2.

      @Preconditions
        Initialize  the TMR2 before calling this function.

      @Param
        periodVal - Value to load into TMR2 register.

      @Returns
        None

      @Example
        <code>
        #define PERIOD1 0x80
        #define PERIOD2 0x40
        #define ZERO    0x00

        while(1)
        {
            // Read the TMR2 register
            if(ZERO == TMR2_ReadTimer())
            {
                // Do something else...

                if(flag)
                {
                    flag = 0;

                    // Load Period 1 value
                    TMR2_LoadPeriodRegister(PERIOD1);
                }
                else
                {
                     flag = 1;

                    // Load Period 2 value
                    TMR2_LoadPeriodRegister(PERIOD2);
                }
            }

            // Do something else...
        }
        </code>
     */
    void TMR2_LoadPeriodRegister(uint8_t periodVal);

    /**
      @Summary
        Boolean routine to poll or to check for the match flag on the fly.

      @Description
        This function is called to check for the timer match flag.
        This function is used in timer polling method.

      @Preconditions
        Initialize  the TMR2 module before calling this routine.

      @Param
        None

      @Returns
        true - timer match has occurred.
        false - timer match has not occurred.

      @Example
        <code>
        while(1)
        {
            // check the match flag
            if(TMR2_HasOverflowOccured())
            {
                // Do something else...

                // Reload the TMR2 value
                TMR2_Reload();
            }
        }
        </code>
     */
    bool TMR2_HasOverflowOccured(void);

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif // _TMR2_H
/**
 End of File
 */

