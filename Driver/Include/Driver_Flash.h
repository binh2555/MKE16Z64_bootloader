#ifndef    _DRIVER_FLASH_H_
#define    _DRIVER_FLASH_H_

#include "HAL_Flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NUMBER_BYTE_PER_SECTOR       (1024U)

typedef enum
{
    FLASH_COMMAND_SUCCESS      = 0x00U,
    FLASH_COMMAND_FAILD        = 0x01U,
}Flash_Status_t;

/*******************************************************************************
 * API
 ******************************************************************************/
Flash_Status_t Driver_Flash_WritePolling(uint32_t startAddress, uint8_t* data, const uint16_t length);

Flash_Status_t Driver_Flash_EraseSector(uint32_t startAddress, uint8_t numOfSecter);

#endif    /* _DRIVER_FLASH_H_ */
/************************************************************
 * END OF _DRIVER_FLASH_H_ FILE
************************************************************/