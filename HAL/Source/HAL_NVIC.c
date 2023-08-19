#include "HAL_NVIC.h"

/**
 * @brief  set enable IQNn
 * @param : IQRn the IQR number
 * @return none
 */
void HAL_NVICEnable(IRQn_Type IQRn)
{
    NVIC_EnableIRQ(IQRn);
}

/**
 * @brief  set disable IQNn
 * @param : IQRn the IQR number
 * @return none
 */
void HAL_NVICDisable(IRQn_Type IQRn)
{
    NVIC_DisableIRQ(IQRn);
}

void HAL_NVIC_SetPriority (IRQn_Type IQRn, uint32_t priority)
{
    NVIC_SetPriority(IQRn, priority);
}
