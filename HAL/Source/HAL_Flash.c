#include "HAL_Flash.h"
#include "MKE16Z4.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define FLASH_CCIF_CLEAR_MASK        (0x80U)

/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @brief  clear Command Complete Interrupt Flag, ckear this flag to launch the current command
 * @param  none
 * @return none
 */
void HAL_FLASH_Clear_CCIF(void)
{
    FTFA->FSTAT = FLASH_CCIF_CLEAR_MASK;
}

/**
 * @brief  write to the Flash Common Command Object Registers 0
 * @param  value    the value will be writed to the Flash Common Command Object Registers 0
 * @return none
 */
void HAL_FLASH_Write_FCCOB0(const uint8_t value)
{
    FTFA->FCCOB0 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 1
 * @param  value    the value will be writed to the Flash Common Command Object Registers 1
 * @return none
 */
void HAL_FLASH_Write_FCCOB1(const uint8_t value)
{
    FTFA->FCCOB1 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 2
 * @param  value    the value will be writed to the Flash Common Command Object Registers 2
 * @return none
 */
void HAL_FLASH_Write_FCCOB2(const uint8_t value)
{
    FTFA->FCCOB2 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 3
 * @param  value    the value will be writed to the Flash Common Command Object Registers 3
 * @return none
 */
void HAL_FLASH_Write_FCCOB3(const uint8_t value)
{
    FTFA->FCCOB3 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 4
 * @param  value    the value will be writed to the Flash Common Command Object Registers 4
 * @return none
 */
void HAL_FLASH_Write_FCCOB4(const uint8_t value)
{
    FTFA->FCCOB4 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 5
 * @param  value    the value will be writed to the Flash Common Command Object Registers 5
 * @return none
 */
void HAL_FLASH_Write_FCCOB5(const uint8_t value)
{
    FTFA->FCCOB5 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 6
 * @param  value    the value will be writed to the Flash Common Command Object Registers 6
 * @return none
 */
void HAL_FLASH_Write_FCCOB6(const uint8_t value)
{
    FTFA->FCCOB6 = value;
}

/**
 * @brief  write to the Flash Common Command Object Registers 7
 * @param  value    the value will be writed to the Flash Common Command Object Registers 7
 * @return none
 */
void HAL_FLASH_Write_FCCOB7(const uint8_t value)
{
    FTFA->FCCOB7 = value;
}

