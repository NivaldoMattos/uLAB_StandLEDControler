
#ifndef _EPWM1_H
#define _EPWM1_H

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

    /**
      Section: EPWM Module APIs
     */

    /**
    @Summary
      Initializes the EPWM1

    @Description
      This routine initializes the EPWM1_Initialize.
      This routine must be called before any other ECCP1 routine is called.
      This routine should only be called once during system initialization.

    @Preconditions
      None

    @Param
      None

    @Returns
      None

    @Comment
    

   @Example
      <code>
      uint16_t dutycycle;

      EPWM1_Initialize();
      EPWM1_LoadDutyValue(dutycycle);
      </code>
     */
    void EPWM1_Initialize(void);
    void EPWM2_Initialize(void);
    void EPWM3_Initialize(void);

    /**
      @Summary
        Loads 16-bit duty cycle.

      @Description
        This routine loads the 16 bit duty cycle value.

      @Preconditions
        EPWM1_Initialize() function should have been called before calling this function.

      @Param
        Pass in 16bit duty cycle value.

      @Returns
        None

      @Example
        <code>
        uint16_t dutycycle;

        EPWM1_Initialize();
        EPWM1_LoadDutyValue(dutycycle);
        </code>
     */
    void EPWM1_LoadDutyValue(uint16_t dutyValue);
    void EPWM2_LoadDutyValue(uint16_t dutyValue);
    void EPWM3_LoadDutyValue(uint16_t dutyValue);
    void EPWM4_LoadDutyValue(uint16_t dutyValue);
    void EPWM5_LoadDutyValue(uint16_t dutyValue);
    
    

#ifdef __cplusplus  // Provide C++ Compatibility

}

#endif

#endif  // _EPWM1_H
/**
 End of File
 */
