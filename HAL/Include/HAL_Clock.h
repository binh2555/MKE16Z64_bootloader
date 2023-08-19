#ifndef    _HAL_CLOCK_H_
#define    _HAL_CLOCK_H_

#include <stdint.h>
#include "header.h"
#include "MKE16Z4.h"


/*******************************************************************************
 * Definition
 ******************************************************************************/
#define FAST_IRC_SPEED      (48000000U)
#define SLOW_IRC_SPEED      (8000000U)

/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief  Enable clock of GPIOB
 * @param  none
 * @return none
 */
void HAL_EnableGPIOBClock(void);

/**
 * @brief  Enable clock of GPIOD
 * @param  none
 * @return none
 */
void HAL_EnableGPIODClock(void);

/**
 * @brief  set FIRCDIV2
 * @param value the value will be set in FIRCDIV2
 * @return none
 */
void HAL_SetFIRCDIV2(uint8_t value);

/**
 * @brief  set PCS LPIT0
 * @param value value will be set in PCS feild of LPIT0
 * @return none
 */
void HAL_SetPCSLPIT0(uint8_t value);

/**
 * @brief  set CGC LPIT0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void HAL_SetCGCLPIT0(uint8_t value);

/**
 * @brief  set PCS LPUART0
 * @param value value will be set in PCS feild of LPIT0
 * @return none
 */
void HAL_SetPCSLPUART0(uint8_t value);

/**
 * @brief  set CGC LPUART0
 * @param value (0) is disable,(1) is enable
 * @return none
 */
void HAL_SetCGCLPUART0(uint8_t value);

void HAL_ENABLE_FTFA_CLOCK(void);

#endif    /* _HAL_CLOCK_H_ */
/*
*END OF DAL_CLOCK.h FILE
*/
