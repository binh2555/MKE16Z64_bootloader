#include "Driver_Flash.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PROGRAM_LONGWORD_COMMAND     (0x06U)
#define ERASE_FLASH_SECTOR_COMMAND   (0x09U)
#define LONGWORD_ALIGNED             (4U)

/**
 * @brief  struct to decode a 32bit address to 4 feild,each feild is 8 bit of 32 bit address 
 */
typedef struct{
    uint8_t addressIndex[4];
}AddressDecode_Struct;

/**
 * @brief  write polling to flash
 * @param  startAddress     the start address of data which is will be writed to flash
 * @param  data             the poiter point to data
 * @param  length           the length of data
 * @return none
 */
Flash_Status_t Driver_Flash_WritePolling(uint32_t startAddress, uint8_t* data, const uint16_t length)
{
    Flash_Status_t writeCommandState = FLASH_COMMAND_SUCCESS;
    uint32_t validStartAddress = 0;
    uint16_t i = 0;    /* variable to count in the for loop */

    HAL_FLASH_Write_FCCOB0(PROGRAM_LONGWORD_COMMAND);    /* set the FCCOB0 is program long word command */

    /**
     * @brief because the startaddres must be a value divisible by 4,so first we need to check the start addres,
     * if the start address is not divisible by 4,handle it
     */
    if ((0 != (startAddress % LONGWORD_ALIGNED)) && (0 < length))
    {
        validStartAddress = ((startAddress / LONGWORD_ALIGNED) * LONGWORD_ALIGNED);

        while (FTFA_READ_CCIF == 0){}    /* wait to previous command complete */

        if (0 != (FTFA_READ_RDCOLERR | FTFA_READ_ACCERR | FTFA_READ_FPVIOL))    /* if the previous command complete with a error, change the state to error state */
        {
            writeCommandState = FLASH_COMMAND_FAILD;
        }
        else
        {
            /* set the address */
            HAL_FLASH_Write_FCCOB3(((AddressDecode_Struct*)(&validStartAddress))->addressIndex[0]);
            HAL_FLASH_Write_FCCOB2(((AddressDecode_Struct*)(&validStartAddress))->addressIndex[1]);
            HAL_FLASH_Write_FCCOB1(((AddressDecode_Struct*)(&validStartAddress))->addressIndex[2]);

            /* set value for value register */
            switch (startAddress - validStartAddress)    /* if the start addres is not divisible by 4,reduce it to the minimun value which is divisible by 4 */
            {
                /* after reduce value, must be offset the reduced value to ensure completeness */

                case 1:
                    HAL_FLASH_Write_FCCOB4(0xFFU);
                    (0 < length) ? (HAL_FLASH_Write_FCCOB5(data[0])) : (HAL_FLASH_Write_FCCOB5(0xFFU));
                    (1 < length) ? (HAL_FLASH_Write_FCCOB6(data[1])) : (HAL_FLASH_Write_FCCOB6(0xFFU));
                    (2 < length) ? (HAL_FLASH_Write_FCCOB7(data[2])) : (HAL_FLASH_Write_FCCOB7(0xFFU));
                    i = 3;
                    break;
                case 2:
                    HAL_FLASH_Write_FCCOB4(0xFFU);
                    HAL_FLASH_Write_FCCOB5(0xFFU);
                    (0 < length) ? (HAL_FLASH_Write_FCCOB6(data[0])) : (HAL_FLASH_Write_FCCOB6(0xFFU));
                    (1 < length) ? (HAL_FLASH_Write_FCCOB7(data[1])) : (HAL_FLASH_Write_FCCOB7(0xFFU));
                    i = 2;
                    break;
                case 3:
                    HAL_FLASH_Write_FCCOB4(0xFFU);
                    HAL_FLASH_Write_FCCOB5(0xFFU);
                    HAL_FLASH_Write_FCCOB6(0xFFU);
                    (0 < length) ? (HAL_FLASH_Write_FCCOB7(data[0])) : (HAL_FLASH_Write_FCCOB7(0xFFU));
                    i = 1;
                    break;

                default:
                    break;
            }

            HAL_FLASH_Clear_CCIF();    /* clear command complete interrupt flag to excute command */

            startAddress = validStartAddress + 4;
        }
    }

    /* after handle the address is not devisible by 4, continue with the remaining data */
    if (writeCommandState == FLASH_COMMAND_SUCCESS)    /* check the previous command have any error ??,if not continue */
    {
        for (; (i + 4) <= length; i += 4)
        {
            while (FTFA_READ_CCIF == 0){}    /* wait to previous command complete */
            if (0 != (FTFA_READ_RDCOLERR | FTFA_READ_ACCERR | FTFA_READ_FPVIOL))
            {
                writeCommandState = FLASH_COMMAND_FAILD;
            }
            else
            {
                HAL_FLASH_Write_FCCOB3(((AddressDecode_Struct*)(&startAddress))->addressIndex[0]);
                HAL_FLASH_Write_FCCOB2(((AddressDecode_Struct*)(&startAddress))->addressIndex[1]);
                HAL_FLASH_Write_FCCOB1(((AddressDecode_Struct*)(&startAddress))->addressIndex[2]);

                HAL_FLASH_Write_FCCOB4(data[i]);
                HAL_FLASH_Write_FCCOB5(data[i + 1]);
                HAL_FLASH_Write_FCCOB6(data[i + 2]);
                HAL_FLASH_Write_FCCOB7(data[i + 3]);

                HAL_FLASH_Clear_CCIF();    /* clear command complete interrupt flag to excute command */
                startAddress += 4;
            }
        }
    }

    /* if still have data in the buffer,continue write to flash*/
    if ((i < length) && (writeCommandState == FLASH_COMMAND_SUCCESS))
    {
        while (FTFA_READ_CCIF == 0){}    /* wait to previous command complete */
        if (0 != (FTFA_READ_RDCOLERR | FTFA_READ_ACCERR | FTFA_READ_FPVIOL))
        {
            writeCommandState = FLASH_COMMAND_FAILD;
        }
        else
        {
            HAL_FLASH_Write_FCCOB3(((AddressDecode_Struct*)(&startAddress))->addressIndex[0]);
            HAL_FLASH_Write_FCCOB2(((AddressDecode_Struct*)(&startAddress))->addressIndex[1]);
            HAL_FLASH_Write_FCCOB1(((AddressDecode_Struct*)(&startAddress))->addressIndex[2]);

            HAL_FLASH_Write_FCCOB4(data[i]);
            ((i + 1) < length) ? (HAL_FLASH_Write_FCCOB5(data[i+1])) : (HAL_FLASH_Write_FCCOB5(0xFFU));
            ((i + 2) < length) ? (HAL_FLASH_Write_FCCOB6(data[i+2])) : (HAL_FLASH_Write_FCCOB6(0xFFU));
            ((i + 3) < length) ? (HAL_FLASH_Write_FCCOB7(data[i+3])) : (HAL_FLASH_Write_FCCOB7(0xFFU));

            HAL_FLASH_Clear_CCIF();    /* clear command complete interrupt flag to excute command */
        }
    }

    if (writeCommandState == FLASH_COMMAND_SUCCESS)
    {
        while (FTFA_READ_CCIF == 0){}    /* wait to previous command complete */
        if (0 != (FTFA_READ_RDCOLERR | FTFA_READ_ACCERR | FTFA_READ_FPVIOL))
        {
            writeCommandState = FLASH_COMMAND_FAILD;
        }
    }

    return writeCommandState;
}

/**
 * @brief  erase the sector in flash memory
 * @param  startAddress     the address of sector
 * @param  numOfSector      the number of sector will be erased
 * @return none
 */
Flash_Status_t Driver_Flash_EraseSector(uint32_t startAddress, uint8_t numOfSecter)
{
    uint8_t count = 0;
    Flash_Status_t eraseCommandState = FLASH_COMMAND_SUCCESS;

    HAL_FLASH_Write_FCCOB0(ERASE_FLASH_SECTOR_COMMAND);    /* set the FCCBO0 is erase commands */
    for (; count < numOfSecter; count++)
    {
        while (FTFA_READ_CCIF == 0){}    /* wait to previous command complete */
        if (0 != (FTFA_READ_RDCOLERR | FTFA_READ_ACCERR | FTFA_READ_FPVIOL))
        {
            eraseCommandState = FLASH_COMMAND_FAILD;
        }
        else
        {
            HAL_FLASH_Write_FCCOB3(((AddressDecode_Struct*)(&startAddress))->addressIndex[0]);
            HAL_FLASH_Write_FCCOB2(((AddressDecode_Struct*)(&startAddress))->addressIndex[1]);
            HAL_FLASH_Write_FCCOB1(((AddressDecode_Struct*)(&startAddress))->addressIndex[2]);

            HAL_FLASH_Clear_CCIF();    /* launch the command */

            startAddress += NUMBER_BYTE_PER_SECTOR;
        }
    }

    if (eraseCommandState == FLASH_COMMAND_SUCCESS)
    {
        while (FTFA_READ_CCIF == 0){}    /* wait to previous command complete */
        if (0 != (FTFA_READ_RDCOLERR | FTFA_READ_ACCERR | FTFA_READ_FPVIOL))
        {
            eraseCommandState = FLASH_COMMAND_FAILD;
        }
    }

    return eraseCommandState;
}
