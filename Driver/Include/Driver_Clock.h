#ifndef    _DRIVER_CLOCK_H
#define    _DRIVER_CLOCK_H

#include "HAL_Clock.h"
#include <stdint.h>

/*******************************************************************************
* Definition
******************************************************************************/

/*!
 * @brief Clock source for peripherals that support various clock selections.
 */
typedef enum
{
    IpSrcNoneOrExt   = 0U, /* Clock is off or external clock is used. */
    IpSrcSysOscAsync = 1U, /* System Oscillator async clock.          */
    IpSrcSircAsync   = 2U, /* Slow IRC async clock.                   */
    IpSrcFircAsync   = 3U, /* Fast IRC async clock.                   */
    IpSrcLpFllAsync  = 5U  /* LPFLL async clock.                      */
} clock_src;

/*!
 * @brief SCG asynchronous clock divider value.
 */
typedef enum
{
    AsyncClkDisable = 0U, /* Clock output is disabled.  */
    AsyncClkDivBy1  = 1U, /* Divided by 1.              */
    AsyncClkDivBy2  = 2U, /* Divided by 2.              */
    AsyncClkDivBy4  = 3U, /* Divided by 4.              */
    AsyncClkDivBy8  = 4U, /* Divided by 8.              */
    AsyncClkDivBy16 = 5U, /* Divided by 16.             */
    AsyncClkDivBy32 = 6U, /* Divided by 32.             */
    AsyncClkDivBy64 = 7U  /* Divided by 64.             */
} async_clk_div;

/*******************************************************************************
* API
******************************************************************************/

/**
 * @brief  enable clock for GPIOB
 * @param : none
 * @return none
 */
void Driver_EnableGPIOBClock(void);

/**
 * @brief  enable clock for GPIOB
 * @param  none
 * @return none
 */
void Driver_EnableGPIOCClock(void);

/**
 * @brief  enable clock for GPIOB
 * @param  none
 * @return none
 */
void Driver_EnableGPIODClock(void);

/**
 * @brief  set FIRCDIV2
 * @param clkDiv the value will be set in FIRCDIV2
 * @return none
 */
void Driver_SetFIRCDIV2(async_clk_div clkDiv);

/**
 * @brief  set PCS LPIT0
 * @param clockSrc clock source for LPIT0
 * @return none
 */
void Driver_SetPCSLPIT0(clock_src clockSrc);

/**
 * @brief  set PCS LPUART0
 * @param clockSrc clock source for LPIT0
 * @return none
 */
void Driver_SetPCSLPUART0(clock_src clockSrc);

/**
 * @brief  set CGC LPIT0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void Driver_SetCGCLPIT0(uint8_t value);

/**
 * @brief  set CGC LPUART0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void Driver_SetCGCLPUART0(uint8_t value);

void Driver_EnableFalshModuleClock(void);

#endif    /* _DRIVER_CLOCK_H */
/********************************************************************************
 *END FILE!!!
 ********************************************************************************/
