#include "Driver_systick.h"

int32_t LPUART_ReceiveTimeout[3] = {-1, -1, -1};
int32_t LPUART_TransmitTimeout[3] = {-1, -1, -1};    /* transmit need timeout or not ?? */

void (*LPUART_timeoutHandle[3])(void) = {NULL, NULL, NULL};

/**
 * @brief  register the handler function for system tick interrupt
 * @param  sysTickFunc the function will be call when system tick interrupt coccured
 * @return none
 */
void Driver_systickInit(const systick_ConfigParaStruct* const configStruct)
{
    /* set clock source */
    switch (configStruct->clkSrc)
    {
        case systick_clock_src_process:
        HAL_ProcessClock_systick();
            break;

        case systick_clock_src_external:
        HAL_ExternalClock_systick();
        break;
    
        default:
            break;
    }

    /* set reload value */
    HAL_SetReloadValue_systick(configStruct->reloadValue);

    /* enable or disable interrupt */
    if (configStruct->interruptEnable)
    {
        HAL_InterrputEnable_systick();
    }
    else
    {
        HAL_InterrputDisable_systick();
    }

    /*enable or disable systick */
    if (configStruct->systickEnable)
    {
        HAL_Enable_systick();
    }
    else
    {
        HAL_Disable_systick();
    }
}

/**
 * @brief  disable or enable systick interrupt
 * @param  None
 * @return none
 */
void Driver_systickInterruptEnableOrDisable(bool value)
{
    if (value)
    {
        HAL_InterrputEnable_systick();
    }
    else
    {
        HAL_InterrputDisable_systick();
    }
}

/**
 * @brief  systick handler function of LPUART timeout,the receiver and transmiter both use a timeout handle function
 * @param  None
 * @return none
 */
void SysTick_Handler(void)
{
    /* handle timeout of receive LPUART0 */
    if (LPUART_ReceiveTimeout[0] > -1)
    {
        LPUART_ReceiveTimeout[0] -= 1;
        if (LPUART_ReceiveTimeout[0] < 0)
        {
            if (NULL != LPUART_timeoutHandle[0])
            {
                LPUART_timeoutHandle[0]();
            }
        }
    }

    /* handle timeout of receive LPUART1 */
    if (LPUART_ReceiveTimeout[1] > -1)
    {
        LPUART_ReceiveTimeout[1] -= 1;
        if (LPUART_ReceiveTimeout[1] < 0)
        {
            if (NULL != LPUART_timeoutHandle[1])
            {
                LPUART_timeoutHandle[1]();
            }
        }
    }

    /* handle timeout of receive LPUART2 */
    if (LPUART_ReceiveTimeout[2] > -1)
    {
        LPUART_ReceiveTimeout[2] -= 1;
        if (LPUART_ReceiveTimeout[2] < 0)
        {
            if (NULL != LPUART_timeoutHandle[2])
            {
                LPUART_timeoutHandle[2]();
            }
        }
    }

        /* handle timeout of transmit LPUART0 */
    if (LPUART_TransmitTimeout[0] > -1)
    {
        LPUART_TransmitTimeout[0] -= 1;
        if (LPUART_TransmitTimeout[0] < 0)
        {
            if (NULL != LPUART_timeoutHandle[0])
            {
                LPUART_timeoutHandle[0]();
            }
        }
    }

    /* handle timeout of transmit LPUART1 */
    if (LPUART_TransmitTimeout[1] > -1)
    {
        LPUART_TransmitTimeout[1] -= 1;
        if (LPUART_TransmitTimeout[1] < 0)
        {
            if (NULL != LPUART_timeoutHandle[1])
            {
                LPUART_timeoutHandle[1]();
            }
        }
    }

    /* handle timeout of transmit LPUART2 */
    if (LPUART_TransmitTimeout[2] > -1)
    {
        LPUART_TransmitTimeout[2] -= 1;
        if (LPUART_TransmitTimeout[2] < 0)
        {
            if (NULL != LPUART_timeoutHandle[2])
            {
                LPUART_timeoutHandle[2]();
            }
        }
    }
}


