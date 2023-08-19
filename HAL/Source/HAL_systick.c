#include "HAL_systick.h"
#include <stdio.h>

static void (*sysTickHandleFunc)(void) = NULL;    /* the function poiter contain the address of function will be called which user have registered */

/**
 * @brief  enable system tick
 * @param  None
 * @return none
 */
void HAL_Enable_systick(void)
{
    SYST_CSR |= (1 << SYSTICK_ENABLE_SHIFT);
}

/**
 * @brief  disable system tick
 * @param  None
 * @return none
 */
void HAL_Disable_systick(void)
{
    SYST_CSR &= ~(1 << SYSTICK_ENABLE_SHIFT);
}

/**
 * @brief  enable interrupt system tick
 * @param  None
 * @return none
 */
void HAL_InterrputEnable_systick(void)
{
    SYST_CSR |= (1 << SYSTICK_TICKINT_SHIFT);
}

/**
 * @brief  disable interrupt system tick
 * @param  None
 * @return none
 */
void HAL_InterrputDisable_systick(void)
{
    SYST_CSR &= ~(1 << SYSTICK_TICKINT_SHIFT);
}

/**
 * @brief  select process clock as clock source for systick module
 * @param  None
 * @return none
 */
void HAL_SetReloadValue_systick(uint32_t reloadValue)
{
    SYST_RVR = ((SYST_RVR & SYSTICK_RVR_MASK) | SYSTICK_RVR_PC(((reloadValue * SYSTICK_CLOCK)-1)));
}

/**
 * @brief  select external clock as clock source for systick module
 * @param  None
 * @return none
 */
void HAL_ProcessClock_systick(void)
{
    SYST_CSR |= (1 << SYSTICK_CLKSOURCE_SHIFT);
}

/**
 * @brief  set reload value for system tick
 * @param  reloadValue reload value is set for system tick
 * @return none
 */
void HAL_ExternalClock_systick(void)
{
    SYST_CSR &= ~(1 << SYSTICK_CLKSOURCE_SHIFT);
}

/**
 * @brief  register the handler function for system tick interrupt
 * @param  sysTickFunc the function will be call when system tick interrupt coccured
 * @return none
 */
void HAL_systickHandleFunc(void (*sysTickFunc)(void))
{
    sysTickHandleFunc = sysTickFunc;
}
