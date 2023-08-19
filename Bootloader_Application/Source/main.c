#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "Queue.h"
#include "checkSREC.h"
#include "Driver_NVIC.h"
#include "Driver_LPUART.h"
#include "Driver_GPIO.h"
#include "Driver_Clock.h"
#include "Driver_Flash.h"
#include "Driver_systick.h"
#include "HAL_systick.h"

/***********************************************************************
 * Definition
***********************************************************************/
#define MAX_BYTE_DATA_IN_SREC_LINE          (255U)
#define MAX_ERROR_COUNT                     (200U)

#define MAX_SECTOR_OF_APPLICATION_REGION    (10U)

#define APLICATION_START_ADDRESS            (0xA000U)
#define APLICATION_END_ADDRESS              (APLICATION_START_ADDRESS + (MAX_SECTOR_OF_APPLICATION_REGION * NUMBER_BYTE_PER_SECTOR))

/***********************************************************************
 * Decleration
***********************************************************************/
/**
 * @brief  state to notice that the what should do
 */
typedef enum{
    ReceiveState_FirstByte = 0x00U,
    ReceiveState_NextThreeBytes,
    ReceiveState_RemainingBytes,
}LPUART_ReceiveState;

/**
 * @brief  define the string which is will be printed to user know the state of program
 */
typedef enum{
    LPUARTNotice_ErrorSrecFileIndex      = 0x00U,
    LPUARTNotice_SrecReceivingIndex      = 0x01U,
    LPUARTNotice_InBootloaderModeIndex   = 0x02U,
    LPUARTNotice_ErrorTimeoutIndex       = 0x03U,
    LPUARTNotice_SuccessIndex            = 0x04U,
    LPUARTNotice_WriteToFlashError       = 0x05U,
}LPUARTStrNoticeIndex_t;

/***********************************************************************
 * Variable
***********************************************************************/
static uint8_t *s_buffLine = NULL;
static volatile bool SRECLineReadyFlag = false;
static volatile bool programState = true;

/**
 * @brief the array contain notifications string to print
 * 
 */
static uint8_t* noticeStr[] = {"ERROR : SREC file is invalid",                 /* meaning : srec file is error */
                               ">",                                            /* meaning : receiving srec file is running */
                               "BOOTLOADER MODE\r\nReceiving SREC file ",      /* meaning : the device is running at bootloader mode */
                               "ERROR : Timeout!!!",                           /* meaning : timeout error */
                               "Receving SREC file SUCCESS!!!",                /* meaning : receiving srec file is success */
                               "ERROR : Write to flash is faild!!!",};         /* meaning : have a error when write to flash memory */
static LPUART_ReceiveState receiveState = ReceiveState_FirstByte;
static uint8_t errorCount = 0;

/**
 * @brief  initialization LPUART0
 * @return none
 */
static void LPUART0_init(void);

/**
 * @brief config systick over each 1 miliseconds to handle timeout fof orther pripheral
 * 
 */
void systick_init(void);

/**
 * @brief  callback function of LPUART0
 * @return none
 */
void LPUART_ReceiveCallbackFunction(void);

/**
 * @brief  initialization LPUART0
 * @return none
 */
void LPUART0_errorHandle(void);

/**
 * @brief count the length of string
 * 
 * @param str string will be counted
 * @return uint16_t the length of string
 */
static uint16_t mystrlen(const uint8_t* str);

/**
 * @brief  erase the application memory region
 * @return none
 */
static void eraseApplicationRegion(void);


/**
 * @brief  bootloader main function
 */
int bootloader_main(void)
{
    uint8_t dataFeildStartPositionInSrecLine = 0;
    uint32_t startAddress = 0;
    uint8_t byteCount = 0;
    uint8_t* SRECLineBuff = NULL;
    uint8_t storeByteDataInSrecLine[MAX_BYTE_DATA_IN_SREC_LINE] = {0};
    uint8_t countByteDataInSrecLine = 0;

    /* init flash module and erase the application flash region befor receiving the new data*/
    Driver_EnableFalshModuleClock();
    eraseApplicationRegion();

    systick_init();
    LPUART0_init();
    s_buffLine = getRxQueueAddress();
    Driver_LPUART_waitToTransmit(mLPUART0, noticeStr[LPUARTNotice_InBootloaderModeIndex],mystrlen(noticeStr[LPUARTNotice_InBootloaderModeIndex]), 5000);
    Driver_LPUART_waitToReceive(mLPUART0, s_buffLine, 1, 15000);
    while(1)
    {
         if (programState != true)    /* if the program state is error, do this code */
         {
            /* do something to handle error */
            Driver_RXEnableOrDisable(mLPUART0, false);
            eraseApplicationRegion();
            Driver_LPUART_waitToTransmit(mLPUART0, noticeStr[LPUARTNotice_ErrorSrecFileIndex], mystrlen(noticeStr[LPUARTNotice_ErrorSrecFileIndex]), 5000);
            /* do something if program state is error */
            while (1)
            {

            }
         }

         else if (true == SRECLineReadyFlag)
         {
             SRECLineReadyFlag = false;
             SRECLineBuff = RX_dequeue();
             if (true == checkLine(SRECLineBuff))
             {
                Driver_LPUART_waitToTransmit(mLPUART0, noticeStr[LPUARTNotice_SrecReceivingIndex],mystrlen(noticeStr[LPUARTNotice_SrecReceivingIndex]), 5000);    /* print '>' to user know that receiver is running*/

                /* decode the address fidle in SREC line */
                if (('1' == SRECLineBuff[1]) || ('2' == SRECLineBuff[1]) || ('3' == SRECLineBuff[1]))
                {
                    byteCount = (convertHexCharToInterger(SRECLineBuff[2]) << 4) | convertHexCharToInterger(SRECLineBuff[3]);
                    switch (SRECLineBuff[1])
                    {
                    case '1':    /* if the line is type S1, get start address and update the bytecount and data feild position in the srec line */
                        startAddress = (convertHexCharToInterger(SRECLineBuff[4]) << 12) | \
                                       (convertHexCharToInterger(SRECLineBuff[5]) << 8)  | \
                                       (convertHexCharToInterger(SRECLineBuff[6]) << 4)  | \
                                       (convertHexCharToInterger(SRECLineBuff[7]));
                        byteCount = byteCount - 3;    /* byte count of data feild = byte in srec line - 1 byte of check sum and 2 byte of address feild */
                        dataFeildStartPositionInSrecLine = 8;
                        break;

                    case '2':    /* if the line is type S2, get start address and update the bytecount and data feild position in the srec line */
                        startAddress = (convertHexCharToInterger(SRECLineBuff[4]) << 20) | \
                                       (convertHexCharToInterger(SRECLineBuff[5]) << 16) | \
                                       (convertHexCharToInterger(SRECLineBuff[6]) << 12) | \
                                       (convertHexCharToInterger(SRECLineBuff[7]) << 8)  | \
                                       (convertHexCharToInterger(SRECLineBuff[8]) << 4)  | \
                                       (convertHexCharToInterger(SRECLineBuff[9]));
                        byteCount = byteCount - 4;    /* byte count of data feild = byte in srec line - 1 byte of check sum and 3 byte of address feild */
                        dataFeildStartPositionInSrecLine = 10;
                        break;

                    case '3':  /* if the line is type S3, get start address and update the bytecount and data feild position in the srec line */
                        startAddress = (convertHexCharToInterger(SRECLineBuff[4])  << 28) | \
                                       (convertHexCharToInterger(SRECLineBuff[5])  << 24) | \
                                       (convertHexCharToInterger(SRECLineBuff[6])  << 20) | \
                                       (convertHexCharToInterger(SRECLineBuff[7])  << 16) | \
                                       (convertHexCharToInterger(SRECLineBuff[8])  << 12) | \
                                       (convertHexCharToInterger(SRECLineBuff[9])  << 8)  | \
                                       (convertHexCharToInterger(SRECLineBuff[10]) << 4)  | \
                                       (convertHexCharToInterger(SRECLineBuff[11]));
                        byteCount = byteCount - 5;    /* byte count of data feild = byte in srec line - 2 byte of check sum and 4 byte of address feild */
                        dataFeildStartPositionInSrecLine = 12;
                        break;

                    default:
                        break;
                    }

                    /**
                     * convert the data in srec line to a data byte to write to flash
                     */
                    for (countByteDataInSrecLine = 0 ; countByteDataInSrecLine < byteCount; countByteDataInSrecLine++)
                    {
                        storeByteDataInSrecLine[countByteDataInSrecLine] = (convertHexCharToInterger(SRECLineBuff[dataFeildStartPositionInSrecLine]) << 4) | \
                                                                            convertHexCharToInterger(SRECLineBuff[dataFeildStartPositionInSrecLine + 1]);
                        dataFeildStartPositionInSrecLine += 2;
                    }

                    /* if address in SREC line is invalid, erase data have written and stop receiving data */
                    if ((startAddress < APLICATION_START_ADDRESS) || ((startAddress + countByteDataInSrecLine) >= APLICATION_END_ADDRESS))
                    {
                        programState = false;
                    }
                    else    /* if address is valid,write data into flash */
                    {
                        Driver_systickInterruptEnableOrDisable(false);
                        Driver_NVICDisable(LPUART0_IRQn);

                        /* if write to flash is faild, erase the data have written, print the notification and stop the program at here */
                        if (FLASH_COMMAND_SUCCESS != Driver_Flash_WritePolling(startAddress, storeByteDataInSrecLine, countByteDataInSrecLine))
                        {
                            eraseApplicationRegion();    /* erase the application memory region */
                            Driver_LPUARTSendArrayPolling(mLPUART0, noticeStr[LPUARTNotice_WriteToFlashError], mystrlen(noticeStr[LPUARTNotice_WriteToFlashError]), 100000);
                            /* dome something */
                            while(1)
                            {
                                
                            }
                        }
                        Driver_NVICEnable(LPUART0_IRQn);
                        Driver_systickInterruptEnableOrDisable(true);
                    }
                }

                /**
                 * @brief if the srec line is type S7 or S8 or S9,receiving file is success,stop the program here
                 * thuc ra em cung khong biet cach nao chinh xac de xac dinh rang file srec da nhan het de dung chuong trinh nen dung tam cac line s7 s8 s9
                 */
                if (('9' == SRECLineBuff[1]) || ('8' == SRECLineBuff[1]) || ('7' == SRECLineBuff[1]))
                {
                    Driver_RXEnableOrDisable(mLPUART0, false);
                    Driver_LPUART_waitToTransmit(mLPUART0, noticeStr[LPUARTNotice_SuccessIndex], mystrlen(noticeStr[LPUARTNotice_SuccessIndex]), 5000);
                    /* do something after receiving data is success */
                    while(1)
                    {

                    }
                }
             }
             else    /* if have a error in SREC line, erase data have written in flash and change the program state to error state */
             {
                eraseApplicationRegion();
                Driver_RXEnableOrDisable(mLPUART0, false);
                Driver_LPUART_waitToTransmit(mLPUART0, noticeStr[LPUARTNotice_ErrorSrecFileIndex], mystrlen(noticeStr[LPUARTNotice_ErrorSrecFileIndex]), 5000);    /* print the notice that have a error */
             }
         }
    }
    return 0;
}

/**
 * @brief  callback function of LPUART0
 * @return none
 */
void LPUART_ReceiveCallbackFunction(void)
{
    switch (receiveState)
    {
        case ReceiveState_FirstByte:
            if (s_buffLine[0] == 'S')    /* if the first character is 'S',receive 3 next character */
            {
                errorCount = 0;
                if (lpuart_waitToRecriveSuccess != Driver_LPUART_waitToReceive(mLPUART0, &(s_buffLine[1]), 3, 1000))
                {
                    /* do something to notice that have error */
                    programState = false;
                }
                receiveState = ReceiveState_NextThreeBytes;
            }
            else
            {
                if (MAX_ERROR_COUNT <= errorCount)
                {
                    /* change device to error state */
                    programState = false;
                }
                else
                {
                    errorCount += 1;
                    Driver_LPUART_waitToReceive(mLPUART0, s_buffLine, 1,1000);
                }
            }
            break;
        case ReceiveState_NextThreeBytes:
            if (lpuart_waitToRecriveSuccess != Driver_LPUART_waitToReceive(mLPUART0, &(s_buffLine[4]),\
            ((((convertHexCharToInterger(s_buffLine[2]) << 4) | convertHexCharToInterger(s_buffLine[3])) * 2) + 2), 1000))
            {
                /* do something to notice that have a error */
                programState = false;
            }
            receiveState = ReceiveState_RemainingBytes;
            break;
        case ReceiveState_RemainingBytes:
            SRECLineReadyFlag = true;
            if (0 == queueRXCheckFull())    /* if queue is not full,get next srec line */
            {
                s_buffLine = getRxQueueAddress();
                if (lpuart_waitToRecriveSuccess != Driver_LPUART_waitToReceive(mLPUART0, s_buffLine, 1, 1000))
                {
                    /* do something to notice that have a error here */
                    programState = false;
                }
            }
            else
            {
                /* handle queue rx full */
                programState = false;
            }
            receiveState = ReceiveState_FirstByte;
            break;

        default:
            break;
    }
}

/**
 * @brief handle error of LPUART0 if timeout occurre
 * 
 */
void LPUART0_errorHandle(void)
{
    Driver_LPUARTSendArrayPolling(mLPUART0, noticeStr[LPUARTNotice_ErrorTimeoutIndex], mystrlen(noticeStr[LPUARTNotice_ErrorTimeoutIndex]), 100000);    /* print the notice that have a error */
    programState = false;
}

/**
 * @brief init LPUART0 moudule
 * 
 */
static void LPUART0_init(void)
{
    lpuart_config_t myConfigPara;
    uint32_t AsyncClkSpeed = 0;
    clock_src myClockSrc = IpSrcFircAsync;
    async_clk_div myClkDiv = AsyncClkDivBy8;

    /* init PB0 and PB1 for TX and RX */
    Driver_EnableGPIOBClock();    /* enable clock for PORTB */
    Driver_Mux(GPIO_B, LPUART0_RXPin, MUX_ALT2_MODE);
    Driver_Mux(GPIO_B, LPUART0_TXPin, MUX_ALT2_MODE);

    /* clock LPUART0 config */
    Driver_SetCGCLPUART0(false);    /* disable clock for LPUART module befor set PCS feild */
    Driver_SetFIRCDIV2(myClkDiv);
    Driver_SetPCSLPUART0(myClockSrc);
    Driver_SetCGCLPUART0(true);

    /* set parameter */
    myConfigPara.parityMode = ParityDisabled;                  /* disable priority mode */
    myConfigPara.dataBitsCount = LPUART_EightDataBits;         /* set 8 bit data mode*/
    myConfigPara.stopBitNum = OneStopBit;                      /* set 1 bit stop */
    myConfigPara.isMsb = false;                                /* set LSB first */
    myConfigPara.baudRate_Bps = 115200;                        /* set baudrate = 115200 */
    myConfigPara.ReceiveCallback = LPUART_ReceiveCallbackFunction;    /* set receive callback function */
    myConfigPara.TransmitCallback = NULL;                      /* set transmit callback function */
    myConfigPara.ErrorCallback = LPUART0_errorHandle;           /* set error callback function */

    /* get LPUART clock speed befor divided */
    switch(myClockSrc)
    {
        case IpSrcNoneOrExt :
        break;

        case IpSrcSysOscAsync :
        break;

        case IpSrcSircAsync :
            AsyncClkSpeed = SLOW_IRC_SPEED;
        break;
        case IpSrcFircAsync :
            AsyncClkSpeed = FAST_IRC_SPEED;
        break;

        case IpSrcLpFllAsync :
        break;

        default :
        break;
    }
    /* get LPUART clock speed after divided */
    switch (myClkDiv)
    {
        case AsyncClkDisable:
        /* do something to notice that have the error */
        break;

        case AsyncClkDivBy1:
        /*  not divided*/
        break;

        case AsyncClkDivBy2:
        AsyncClkSpeed /= 2;
        break;

        case AsyncClkDivBy4:
        AsyncClkSpeed /= 4;
        break;

        case AsyncClkDivBy8:
        AsyncClkSpeed /= 8;
        break;
        case AsyncClkDivBy16:
        AsyncClkSpeed /= 16;
        break;

        case AsyncClkDivBy32:
        AsyncClkSpeed /= 32;
        break;

        case AsyncClkDivBy64:
        AsyncClkSpeed /= 64;
        break;

        default:
        /* do something to notice that have the error */
        break;
    }
    myConfigPara.clockSpeed = AsyncClkSpeed;

    /* set priority for LPUART0 interrupt is level 1 to give the level 0 for systick to the timeout work propely */
    Driver_NVIC_SetPriority(LPUART0_IRQn, 1);

    /* enable NVIC for LPUART0 module*/
    Driver_NVICEnable(LPUART0_IRQn);

    /* init module LPUART0 */
    Driver_LPUARTInit(mLPUART0, &myConfigPara);

}

/**
 * @brief config systick over each 1 miliseconds to handle timeout fof orther pripheral
 * 
 */
void systick_init(void)
{
    systick_ConfigParaStruct mySicktickConfig;
    mySicktickConfig.clkSrc = systick_clock_src_process;
    mySicktickConfig.reloadValue = 1000;    /* systick is over after 1ms */
    mySicktickConfig.interruptEnable = true;
    mySicktickConfig.systickEnable = true;
    Driver_systickInit(&mySicktickConfig);
}

/**
 * @brief  erase the application memory region
 * @return none
 */
static void eraseApplicationRegion(void)
{
    Driver_systickInterruptEnableOrDisable(false);
    Driver_NVICDisable(LPUART0_IRQn);
    Driver_Flash_EraseSector(APLICATION_START_ADDRESS, MAX_SECTOR_OF_APPLICATION_REGION);
    Driver_NVICEnable(LPUART0_IRQn);
    Driver_systickInterruptEnableOrDisable(true);
}

/**
 * @brief count the length of string
 * 
 * @param str string will be counted
 * @return uint16_t the length of string
 */
static uint16_t mystrlen(const uint8_t* str)
{
    uint16_t count = 0;
    while('\0' != str[count])
    {
        count++;
    }
    return count;
}
