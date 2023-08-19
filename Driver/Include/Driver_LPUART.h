#ifndef _DRIVER_LPUART_H_
#define _DRIVER_LPUART_H_

#include <stdint.h>
#include <stdbool.h>
#include "HAL_LPUART.h"

/***************************************************************
 * Definition
****************************************************************/
#define LPUART0_TXPin        (1U)    /* define transmit pin number of LPUART0 */
#define LPUART0_RXPin        (0U)    /* define receive pin number of LPUART0 */

typedef void (*LPUART_CallbackFunc)(void);    /* tydef the variable type function poiter */

/***************************************************************
 * Decleration
****************************************************************/

/*! @brief LPUART number. */
typedef enum
{
    lpuart_waitToRecriveSuccess  = 0x0U,
    lpuart_waitToReceiveFaild    = 0x1U,
} LPUART_receive_status;

/**
 * @brief 
 * 
 */
typedef enum
{
    lpuart_waitToTransmitSuccess  = 0x0U,
    lpuart_waitToTransmitFaild    = 0x1U,
} LPUART_transmit_status;

/*! @brief LPUART number. */
typedef enum
{
    mLPUART0 = 0x0U,
    mLPUART1 = 0x1U,
    mLPUART2 = 0x2U
} lpuart_n;

/*! @brief LPUART data bits count. */
typedef enum
{
    LPUART_SevenDataBits = 0x0U,  /*!< Seven data bit */
    LPUART_EightDataBits = 0x1U,  /*!< Eight data bit */
    LPUART_NineDataBits  = 0x2U,  /*!< Nine data bit */
    LPUART_TenDataBits  = 0x3U,   /*!< Ten data bit */
} lpuart_data_bits_t;

/*! @brief LPUART stop bits count. */
typedef enum
{
    OneStopBit = 0x0U, /*!< 1 stop bit */
    TwoStopBit = 0x1U, /*!< 2 stop bit */
} lpuart_stop_bits_t;

/*! @brief LPUART parity mode. */
typedef enum
{
    ParityDisabled = 0x0U, /*!< Parity disabled */
    ParityEven     = 0x2U, /*!< Parity enabled, type even, bit setting: PE|PT = 10 */
    ParityOdd      = 0x3U, /*!< Parity enabled, type odd,  bit setting: PE|PT = 11 */
} lpuart_parity_mode_t;

/*! @brief LPUART configuration structure. */
typedef struct
{
    uint32_t baudRate_Bps;              /*!< LPUART baud rate  */
    lpuart_parity_mode_t parityMode;    /*!< Parity mode, disabled (default), even, odd */
    lpuart_data_bits_t dataBitsCount;   /*!< Data bits count, eight (default), seven */
    uint8_t isMsb;                       /*!< Data bits order, LSB (default), MSB */
    bool RXInterrupt;                   /* true = enalbe
                                          * false = disable
                                          */
    bool TXInterrupt;                   /* true = enalbe
                                          * false = disable
                                          */
    lpuart_stop_bits_t stopBitNum;       /* 0 = 1 stop bit
                                          *1 = 2 stop bit
                                          */
    bool RXFIFO;                        /* true = disable
                                          *false = enalbe
                                          */
    bool TXFIFO;                        /* true = disable
                                          *false = enalbe
                                          */
    uint8_t TXWATER;                    /* set value for TXWATER */
    uint8_t RXWATER;                    /* set value for RXWATER */
    uint32_t clockSpeed;                /* clock speed of module LPUART */

    LPUART_CallbackFunc ReceiveCallback;     /* recevie callback function */
    LPUART_CallbackFunc TransmitCallback;    /* transmit callback function */
    LPUART_CallbackFunc ErrorCallback;       /* error callback function */
} lpuart_config_t;


/*************************************************************************************************
 * API
**************************************************************************************************/

/**
 * @brief  config LPUART module
 * @param configPara   the parameter structure
 * @return none
 */
void Driver_LPUARTInit(lpuart_n lpuartBase, const lpuart_config_t* configPara);

/**
 * @brief  enable or disable transmiter
 * @param lpuartBase   LPUART number module
 * @param value        true or false
 * @return none
 */
void Driver_TXEnableOrDisable(lpuart_n lpuartBase, const bool value);

/**
 * @brief  enable or disable transmiter
 * @param lpuartBase   LPUART number module
 * @param value        true or false
 * @return none
 */
void Driver_RXEnableOrDisable(lpuart_n lpuartBase, const bool value);

/**
 * @brief  send string through LPUART module
 * @param lpuartBase   LPUART number module
 * @param data         data to send
 * @param sizeOfData   the number of data
 * @return none
 */
void Driver_LPUARTSendArrayPolling(lpuart_n lpuartBase, const uint8_t* data, const uint16_t sizeOfData, const uint32_t timeOut);

/**
 * @brief  send a character through LPUART module
 * @param lpuartBase   LPUART number module
 * @param data         data to send
 * @return none
 */
void Driver_LPUARTSendCharPolling(lpuart_n lpuartBase, const uint8_t data, uint32_t timeOut);

/**
 * @brief  read transmit interrupt status
 * @param lpuartBase         LPUART number module
 * @param value   true = enable, false = disable
 * @return none
 */
void Driver_LPUART_EnableOrDisableTXInterrupt(lpuart_n lpuartBase, const bool value);

/**
 * @brief  read transmit interrupt status
 * @param lpuartBase         LPUART number module
 * @param value   true = enable, false = disable
 * @return none
 */
void Driver_LPUART_EnableOrDisableRXInterrupt(lpuart_n lpuartBase, const bool value);

/**
 * @brief  LPUART module wait to receive function
 * @param lpuartBase  LPUART number module
 * @param bufffer     the buffer to store receiving data
 * @param length      the length of receving data will be received
 * @param timeout     timeout value by miliseconds
 * @return this function retern the status code
 */
LPUART_receive_status Driver_LPUART_waitToReceive(lpuart_n lpuartBase, uint8_t* bufffer, const uint16_t length, const uint16_t timeout);

/**
 * @brief  LPUART module wait to transmit function
 * @param lpuartBase  LPUART number module
 * @param bufffer     the buffer to store receiving data
 * @param length      the length of receving data will be received
 * @param timeout     timeout value by miliseconds
 * @return this function retern the status code
 */
LPUART_transmit_status Driver_LPUART_waitToTransmit(lpuart_n lpuartBase, uint8_t* bufffer, const uint16_t length, const uint16_t timeout);
#endif    /* _DRIVER_LPUART_H_ */
/**
 * END OF DRIVER_LPUART.H
 */
