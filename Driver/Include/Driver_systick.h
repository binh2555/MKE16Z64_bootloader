#ifndef _DRIVER_SYSTICK_H_
#define _DRIVER_SYSTICK_H_

#include "HAL_systick.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    systick_clock_src_process = 0x00U,
    systick_clock_src_external = 0x01U,
}systick_clkSrc_t;

typedef struct
{
    uint32_t reloadValue;
    bool interruptEnable;
    systick_clkSrc_t clkSrc;
    bool systickEnable;
}systick_ConfigParaStruct;

typedef void (*Systick_CallbackFunc)(void);    /* tydef the variable type function poiter */


/**
 * @brief  register the handler function for system tick interrupt
 * @param  sysTickFunc the function will be call when system tick interrupt coccured
 * @return none
 */
void Driver_systickInit(const systick_ConfigParaStruct* const configStruct);

void Driver_systickInterruptEnableOrDisable(bool value);

#endif    /* _DRIVER_SYSTICK_H_ */
