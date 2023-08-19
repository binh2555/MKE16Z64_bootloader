#include "Driver_NVIC.h"

/**
 * @brief  enable or disable the interrupt of IQRn
 * @param  IQRn     IQR number
 * @return none
 */
void Driver_NVICEnable(IRQn_Type IQRn)
{
    HAL_NVICEnable(IQRn);
}

/**
 * @brief  disable the interrupt of IQRn
 * @param  IQRn     IQR number
 * @return none
 */
void Driver_NVICDisable(IRQn_Type IQRn)
{
    HAL_NVICDisable(IQRn);
}

/**
 * @brief  set priority of interrupt
 * @param  IQRn     IQR number
 * @param  priority the priority level
 * @return none
 */
void Driver_NVIC_SetPriority (IRQn_Type IQRn, uint32_t priority)
{
    HAL_NVIC_SetPriority(IQRn, priority);
}



