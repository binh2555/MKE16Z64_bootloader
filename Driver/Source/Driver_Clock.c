#include "Driver_Clock.h"

/**
 * @brief  enable clock for GPIOB
 * @param : none
 * @return none
 */
void Driver_EnableGPIOBClock(void)
{
    HAL_EnableGPIOBClock();
}

/**
 * @brief  enable clock for GPIOB
 * @param : none
 * @return none
 */
void Driver_EnableGPIOCClock(void)
{
    
}

/**
 * @brief  enable clock for GPIOB
 * @param : none
 * @return none
 */
void Driver_EnableGPIODClock(void)
{
    HAL_EnableGPIODClock();
}

/**
 * @brief  set FIRCDIV2
 * @param clkDiv the value will be set in FIRCDIV2
 * @return none
 */
void Driver_SetFIRCDIV2(async_clk_div clkDiv)
{
    HAL_SetFIRCDIV2(clkDiv);
}

/**
 * @brief  set PCS LPIT0
 * @param clockSrc clock source for LPIT0
 * @return none
 */
void Driver_SetPCSLPIT0(clock_src clockSrc)
{
    HAL_SetPCSLPIT0(clockSrc);
}

/**
 * @brief  set CGC LPIT0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void Driver_SetCGCLPIT0(uint8_t value)
{
    HAL_SetCGCLPIT0(value);
}

/**
 * @brief  set PCS LPUART0
 * @param clockSrc clock source for LPIT0
 * @return none
 */
void Driver_SetPCSLPUART0(clock_src clockSrc)
{
    HAL_SetPCSLPUART0(clockSrc);
}

/**
 * @brief  set CGC LPUART0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void Driver_SetCGCLPUART0(uint8_t value)
{
    HAL_SetCGCLPUART0(value);
}

void Driver_EnableFalshModuleClock(void)
{
    HAL_ENABLE_FTFA_CLOCK();  /* enable clock for flash module */
}


