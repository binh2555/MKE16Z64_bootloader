#ifndef _DRIVER_NVIC_H_
#define _DRIVER_NVIC_H_

#include "HAL_NVIC.h"

/******************************************************************
*API
******************************************************************/

/**
 * @brief  enable the interrupt of IQRn
 * @param  IQRn     IQR number
 * @return none
 */
void Driver_NVICEnable(IRQn_Type IQRn);

/**
 * @brief  disable the interrupt of IQRn
 * @param  IQRn     IQR number
 * @return none
 */
void Driver_NVICDisable(IRQn_Type IQRn);


/**
 * @brief  set priority of interrupt
 * @param  IQRn     IQR number
 * @param  priority the priority level
 * @return none
 */
void Driver_NVIC_SetPriority (IRQn_Type IQRn, uint32_t priority);

#endif    /* _DRIVER_NVIC_H_ */
/**
 * end of DRIVER_NVIC.H file
 * 
 */