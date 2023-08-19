#ifndef    _HAL_FLASH_H_
#define    _HAL_FLASH_H_

#include <stdint.h>
#include "header.h"
#include "MKE16Z4.h"


/*******************************************************************************
 * Definition
 ******************************************************************************/
#define FLASH_CCIF_SHIFT           (7U)
#define FTFA_READ_CCIF             (FTFA->FSTAT & (1U << FLASH_CCIF_SHIFT))

#define FLASH_RDCOLERR_SHIFT       (6U)
#define FTFA_READ_RDCOLERR         (FTFA->FSTAT & (1U << FLASH_RDCOLERR_SHIFT))

#define FLASH_ACCERR_SHIFT         (5U)
#define FTFA_READ_ACCERR           (FTFA->FSTAT & (1U << FLASH_ACCERR_SHIFT))

#define FLASH_FPVIOL_SHIFT         (4U)
#define FTFA_READ_FPVIOL           (FTFA->FSTAT & (1U << FLASH_FPVIOL_SHIFT))

/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief  clear Command Complete Interrupt Flag, ckear this flag to launch the current command
 * @param  none
 * @return none
 */
void HAL_FLASH_Clear_CCIF(void);

/**
 * @brief  write to the Flash Common Command Object Registers 0
 * @param  value    the value will be writed to the Flash Common Command Object Registers 0
 * @return none
 */
void HAL_FLASH_Write_FCCOB0(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 1
 * @param  value    the value will be writed to the Flash Common Command Object Registers 1
 * @return none
 */
void HAL_FLASH_Write_FCCOB1(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 2
 * @param  value    the value will be writed to the Flash Common Command Object Registers 2
 * @return none
 */
void HAL_FLASH_Write_FCCOB2(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 3
 * @param  value    the value will be writed to the Flash Common Command Object Registers 3
 * @return none
 */
void HAL_FLASH_Write_FCCOB3(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 4
 * @param  value    the value will be writed to the Flash Common Command Object Registers 4
 * @return none
 */
void HAL_FLASH_Write_FCCOB4(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 5
 * @param  value    the value will be writed to the Flash Common Command Object Registers 5
 * @return none
 */
void HAL_FLASH_Write_FCCOB5(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 6
 * @param  value    the value will be writed to the Flash Common Command Object Registers 6
 * @return none
 */
void HAL_FLASH_Write_FCCOB6(const uint8_t value);

/**
 * @brief  write to the Flash Common Command Object Registers 7
 * @param  value    the value will be writed to the Flash Common Command Object Registers 7
 * @return none
 */
void HAL_FLASH_Write_FCCOB7(const uint8_t value);

#endif    /* _HAL_FLASH_H_ */
/*
*END OF HAL_FLASH.h FILE
*/
