#ifndef _HAL_NVIC_H_
#define _HAL_NVIC_H_

#include "MKE16Z4.h"
#include <stdint.h>

/**
 * @brief  set enable IQNn
 * @param : IQRn the IQR number
 * @return none
 */
void HAL_NVICEnable(IRQn_Type IQRn);

/**
 * @brief  set disable IQNn
 * @param : IQRn the IQR number
 * @return none
 */
void HAL_NVICDisable(IRQn_Type IQRn);

void HAL_NVIC_SetPriority (IRQn_Type IQRn, uint32_t priority);

#endif    /* _HAL_NVIC_H_ */
/**
*end of HAL_NVIC.h file
*/
