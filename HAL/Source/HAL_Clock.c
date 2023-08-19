#include "HAL_Clock.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define PCS_MASK           (0xF8FFFFFFU)
#define PCS_SHIFT          (24U)
#define PCS_W(X,Y)         (((X) & PCS_MASK) | ((Y) << PCS_SHIFT))

#define CGC_MASK           (0xBFFFFFFFU)
#define CGC_SHIFT          (30U)
#define CGC_W(X,Y)         (((X) & CGC_MASK) | ((Y) << CGC_SHIFT))

/**
 * @brief  Enable clock of GPIOB
 * @param  none
 * @return none
 */
void HAL_EnableGPIOBClock(void)
{
    PCC->CLKCFG[PCC_PORTB_INDEX] |= (1 << 30);
}

/**
 * @brief  Enable clock of GPIOD
 * @param  none
 * @return none
 */
void HAL_EnableGPIODClock(void)
{
    PCC->CLKCFG[PCC_PORTD_INDEX] |= (1 << 30);
}

/**
 * @brief  set FIRCDIV2
 * @param value the value will be set in FIRCDIV2
 * @return none
 */
void HAL_SetFIRCDIV2(uint8_t value)
{
    SCG->FIRCDIV |= (value << 8);
}

/**
 * @brief  set PCS LPIT0
 * @param value value will be set in PCS feild of LPIT0
 * @return none
 */
void HAL_SetPCSLPIT0(uint8_t value)
{
    PCC->CLKCFG[PCC_LPIT0_INDEX] = PCS_W(PCC->CLKCFG[PCC_LPIT0_INDEX], value);
}

/**
 * @brief  set PCS LPUART0
 * @param value value will be set in PCS feild of LPIT0
 * @return none
 */
void HAL_SetPCSLPUART0(uint8_t value)
{
    PCC->CLKCFG[PCC_LPUART0_INDEX] = PCS_W(PCC->CLKCFG[PCC_LPUART0_INDEX], value);
}

/**
 * @brief  set CGC LPIT0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void HAL_SetCGCLPIT0(uint8_t value)
{
    PCC->CLKCFG[PCC_LPIT0_INDEX] = CGC_W(PCC->CLKCFG[PCC_LPIT0_INDEX], value);
}

/**
 * @brief  set CGC LPUART0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void HAL_SetCGCLPUART0(uint8_t value)
{
    PCC->CLKCFG[PCC_LPUART0_INDEX] = CGC_W(PCC->CLKCFG[PCC_LPUART0_INDEX], value);
}

void HAL_ENABLE_FTFA_CLOCK(void)
{
    PCC->CLKCFG[PCC_FLASH_INDEX] |= (1 << 30);  /* enable clock for flash module */
}