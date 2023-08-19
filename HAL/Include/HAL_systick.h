#ifndef    _HAL_SYSTICK_H_
#define    _HAL_SYSTICK_H_

#include <stdint.h>


#define    SYST_CSR           (*((uint32_t*)0xE000E010U))
#define    SYST_RVR           (*((uint32_t*)0xE000E014U))
#define    SYST_CVR           (*((uint32_t*)0xE000E018U))
#define    SYST_CALIB         (*((uint32_t*)0xE000E01CU))

#define SYSTICK_CLOCK        (48U)    /* process clock */

#define SYSTICK_ENABLE_MASK            (0xFFFFFFFEU)
#define SYSTICK_ENABLE_SHIFT           (0U)
#define SYSTICK_ENABLE_PC(X)           (X << SYSTICK_ENABLE_SHIFT)

#define SYSTICK_TICKINT_MASK           (0xFFFFFFFDU)
#define SYSTICK_TICKINT_SHIFT          (1U)
#define SYSTICK_TICKINT_PC(X)          (X << SYSTICK_TICKINT_SHIFT)

#define SYSTICK_CLKSOURCE_MASK         (0xFFFFFFFBU)
#define SYSTICK_CLKSOURCE_SHIFT        (2U)
#define SYSTICK_CLKSOURCE_PC(X)        (X << SYSTICK_CLKSOURCE_SHIFT)

#define SYSTICK_RVR_MASK               (0xFF000000U)
#define SYSTICK_RVR_SHIFT              (0U)
#define SYSTICK_RVR_PC(X)              (X << SYSTICK_RVR_SHIFT)

/**
 * @brief  register the handler function for system tick interrupt
 * @param  sysTickFunc the function will be call when system tick interrupt coccured
 * @return none
 */
void HAL_systickHandleFunc(void (*sysTickFunc)(void));

/**
 * @brief  enable system tick
 * @param  None
 * @return none
 */
void HAL_Enable_systick(void);

/**
 * @brief  disable system tick
 * @param  None
 * @return none
 */
void HAL_Disable_systick(void);

/**
 * @brief  enable interrupt system tick
 * @param  None
 * @return none
 */
void HAL_InterrputEnable_systick(void);

/**
 * @brief  disable interrupt system tick
 * @param  None
 * @return none
 */
void HAL_InterrputDisable_systick(void);

/**
 * @brief  select process clock as clock source for systick module
 * @param  None
 * @return none
 */
void HAL_ProcessClock_systick(void);

/**
 * @brief  select external clock as clock source for systick module
 * @param  None
 * @return none
 */
void HAL_ExternalClock_systick(void);

/**
 * @brief  set reload value for system tick
 * @param  reloadValue reload value is set for system tick
 * @return none
 */
void HAL_SetReloadValue_systick(uint32_t reloadValue);

#endif    /* _HAL_SYSTICK_H_ */
