#include "Driver_LPUART.h"
#include <stdio.h>

/*******************************************************************************************
 * Definition
********************************************************************************************/
#define NUMBER_LPUART_MODULE     (0x3U)    /* number module LPUART in device */

/*******************************************************************************************
 * Decleration
********************************************************************************************/
/**
 * LPUART transmiter and receiver status, free or idle
*/
typedef enum{
    LPUART_STATUS_BUSY   = 0x00U,
    LPUART_STATUS_IDLE   = 0x01U
}LPUART_Status_t;

/**
 * @brief struct contain the info of receiver and transmiter of LPUART,
 * include buffer, status, count value and length
 * 
 */
typedef struct{
    uint8_t* LPUART_buffer;
    LPUART_Status_t status;
    uint16_t LPUART_dataCount;
    uint16_t LPUART_length;
}LPUART_Struct_dataInfo;

/*******************************************************************************************
 * Variable
********************************************************************************************/
extern LPUART_Type * basePtrLPUART[];
extern void (*LPUART_timeoutHandle[3])(void);    /* the timeout handle func */
extern int32_t LPUART_ReceiveTimeout[];          /* the receive timeout count in Driver_systick.c file */
extern int32_t LPUART_TransmitTimeout[];         /* the transmit timeout count in Driver_systick.c file */

static LPUART_CallbackFunc LPUART_ReceiveCallback[NUMBER_LPUART_MODULE]  = {NULL, NULL, NULL};    /* the receive callback function for LPUART, LPUART_ReceiveCallback[x] = LPUART_x receive callback */
static LPUART_CallbackFunc LPUART_TransmitCallback[NUMBER_LPUART_MODULE] = {NULL, NULL, NULL};    /* the receive callback function for LPUART, LPUART_TransmitCallback[x] = LPUART_x transmit callback */

/* informaion of LPUART receive status */
static LPUART_Struct_dataInfo receiveDataStructure[NUMBER_LPUART_MODULE] = {{NULL, LPUART_STATUS_IDLE, 0, 0},
                                                                            {NULL, LPUART_STATUS_IDLE, 0, 0},
                                                                            {NULL, LPUART_STATUS_IDLE, 0, 0}};

/* informaion of LPUART transmit status */
static LPUART_Struct_dataInfo transmitDataStructure[NUMBER_LPUART_MODULE] = {{NULL, LPUART_STATUS_IDLE, 0, 0},
                                                                             {NULL, LPUART_STATUS_IDLE, 0, 0},
                                                                             {NULL, LPUART_STATUS_IDLE, 0, 0}};

/*******************************************************************************************
 * API
********************************************************************************************/

/**
 * @brief  this function check the lpuartbase is valid or invalid,if invalid, this function will be stoped
 * @param lpuartBase  LPUART number module
 * @return none
 */
static void checkParameter(lpuart_n lpuartbase);

static void checkParameter(lpuart_n lpuartbase)
{
    switch (lpuartbase)
    {
    case mLPUART0:
        /* code */
        break;
    case mLPUART1:
        /* code */
        break;
    case mLPUART2:
        /* code */
        break;

    default:
        while(1)
        {
            /* do something to notice that have a error */
        }
        break;
    }
}

/**
 * @brief  config LPUART module
 * @param configPara   the parameter structure
 * @return none
 */
void Driver_LPUARTInit(lpuart_n lpuartBase, const lpuart_config_t* configPara)
{
    uint8_t OSRCount = 0;
    uint16_t SBRCount = 0;
    uint32_t errorCount = INT32_MAX;
    int32_t currentErrorCount = 0;
    uint32_t lpuartClockFrequen = configPara->clockSpeed;
    uint8_t OSR = 0;
    uint16_t SBR = 0;

    checkParameter(lpuartBase);

    /* disable TX and RX befor set parameter of LPUART module */
    HAL_LPUART_Write_TE(basePtrLPUART[lpuartBase], false);
    HAL_LPUART_Write_RE(basePtrLPUART[lpuartBase], false);

    /* set data bits */
    switch (configPara->dataBitsCount)
    {
        /* set bit M10 = 0, M7 = 1 to running as 7 bit data mode */
        case LPUART_SevenDataBits:
            HAL_LPUART_Write_M10(basePtrLPUART[lpuartBase], 0);
            HAL_LPUART_Write_M7(basePtrLPUART[lpuartBase], 1);
            break;
        /* set bit M10 = 0, M7 = 1, M = 0 to running as 8 bit data mode */
        case LPUART_EightDataBits:
            HAL_LPUART_Write_M10(basePtrLPUART[lpuartBase], 0);
            HAL_LPUART_Write_M7(basePtrLPUART[lpuartBase], 0);
            HAL_LPUART_Write_M(basePtrLPUART[lpuartBase], 0);
            break;
        /* set bit M10 = 0, M7 = 0, M = 1 to running as 9 bit data mode */
        case LPUART_NineDataBits:
            HAL_LPUART_Write_M10(basePtrLPUART[lpuartBase], 0);
            HAL_LPUART_Write_M7(basePtrLPUART[lpuartBase], 0);
            HAL_LPUART_Write_M(basePtrLPUART[lpuartBase], 1);
            break;
        /* set bit M10 = 1, M7 = 0 to running as 10 bit data mode */
        case LPUART_TenDataBits:
            HAL_LPUART_Write_M10(basePtrLPUART[lpuartBase], 1);
            HAL_LPUART_Write_M7(basePtrLPUART[lpuartBase], 0);
            break;
    
        default:
            break;
    }

    /* priority mode */
    switch (configPara->parityMode)
    {
    case ParityDisabled:
        HAL_LPUART_Write_PE(basePtrLPUART[lpuartBase], 0);    /* set bit PE = 0 to disable parity */
        break;
    case ParityEven:
        HAL_LPUART_Write_PE(basePtrLPUART[lpuartBase], 1);    /* set bit PE = 1 to enable parity */
        HAL_LPUART_Write_PT(basePtrLPUART[lpuartBase], 0);    /* set bit Pt = 0 to set even parity type */
        break;
    case ParityOdd:
        HAL_LPUART_Write_PE(basePtrLPUART[lpuartBase], 1);    /* set bit PE = 1 to enable parity */
        HAL_LPUART_Write_PT(basePtrLPUART[lpuartBase], 1);    /* set bit Pt = 1 to set odd parity type */
        break;

    default:
        break;
    }

    /* set stop bit number */
    HAL_LPUART_Write_SBNS(basePtrLPUART[lpuartBase], configPara->stopBitNum);

    /* set MSB bit */
    HAL_LPUART_Write_MSBF(basePtrLPUART[lpuartBase], configPara->isMsb);

    /* find OSR and SBR and set these value */
    for (OSRCount = 4; OSRCount <= 31; OSRCount++)
    {
        for (SBRCount = 1; SBRCount <= 8191; SBRCount++)
        {
            currentErrorCount = (lpuartClockFrequen / (SBRCount * (OSRCount + 1))) - configPara->baudRate_Bps;
            if (currentErrorCount < 0)
            {
                currentErrorCount *= -1;
            }
            if (currentErrorCount < errorCount)
            {
                OSR = OSRCount;
                SBR = SBRCount;
                errorCount = currentErrorCount;
            }
        }
    }
    HAL_LPUART_Write_OSR(basePtrLPUART[lpuartBase], OSR);    /* set OSR after caculate the best value */
    HAL_LPUART_Write_SBR(basePtrLPUART[lpuartBase], SBR);    /* set SBR after caculate the best value */

    /* set callback function for LPUART */
    LPUART_ReceiveCallback[lpuartBase] = configPara->ReceiveCallback;
    LPUART_TransmitCallback[lpuartBase] = configPara->TransmitCallback;
    LPUART_timeoutHandle[lpuartBase] = configPara->ErrorCallback;

    /* enable TX and RX after set parameter for LPUART module */
    HAL_LPUART_Write_RE(basePtrLPUART[lpuartBase], true);
    HAL_LPUART_Write_TE(basePtrLPUART[lpuartBase], true);
}

/**
 * @brief  enable or disable transmiter
 * @param lpuartBase   LPUART number module
 * @param value        true or false
 * @return none
 */
void Driver_TXEnableOrDisable(lpuart_n lpuartBase, const bool value)
{
    checkParameter(lpuartBase);
    HAL_LPUART_Write_TE(basePtrLPUART[lpuartBase], value);
}

/**
 * @brief  enable or disable transmiter
 * @param lpuartBase   LPUART number module
 * @param value        true or false
 * @return none
 */
void Driver_RXEnableOrDisable(lpuart_n lpuartBase, const bool value)
{
    checkParameter(lpuartBase);
    if (false == value)
    {
        LPUART_ReceiveTimeout[lpuartBase] = -1;    /* disable timeout of LPUART if receiver is disable*/
    }
    HAL_LPUART_Write_RE(basePtrLPUART[lpuartBase], value);
}

/**
 * @brief  send string through LPUART module
 * @param lpuartBase   LPUART number module
 * @param data         data to send
 * @param sizeOfData   the number of data
 * @return none
 */
void Driver_LPUARTSendArrayPolling(lpuart_n lpuartBase, const uint8_t* data, const uint16_t sizeOfData, const uint32_t timeOut)
{
    uint16_t cnt = 0;

    checkParameter(lpuartBase);
    while (cnt < sizeOfData)
    {
       Driver_LPUARTSendCharPolling(lpuartBase, data[cnt], 1000000);
       cnt++;
    }
}

/**
 * @brief  send a character through LPUART module
 * @param lpuartBase   LPUART number module
 * @param data         data to send
 * @return none
 */
void Driver_LPUARTSendCharPolling(lpuart_n lpuartBase, const uint8_t data, uint32_t timeOut)
{
    checkParameter(lpuartBase);

    // while(0 == Driver_LPUART_Read_TransmitEmptyFlag(lpuartBase) && timeOut)
    while((0 == HAL_LPUART_Read_TDRE(basePtrLPUART[lpuartBase])) && timeOut)
    {
        timeOut--;
    }
    if (timeOut)
    {
        HAL_LPUART_Write_DATA(basePtrLPUART[lpuartBase], data);
    }
}

/**
 * @brief  read transmit interrupt status
 * @param lpuartBase         LPUART number module
 * @param value   true = enable, false = disable
 * @return none
 */
void Driver_LPUART_EnableOrDisableTXInterrupt(lpuart_n lpuartBase, const bool value)
{
    checkParameter(lpuartBase);
    HAL_LPUART_Write_TIE(basePtrLPUART[lpuartBase], value);    /* set TX interrupt */
}

/**
 * @brief  read transmit interrupt status
 * @param lpuartBase         LPUART number module
 * @param value   true = enable, false = disable
 * @return none
 */
void Driver_LPUART_EnableOrDisableRXInterrupt(lpuart_n lpuartBase, const bool value)
{
    HAL_LPUART_Write_RIE(basePtrLPUART[lpuartBase], value);
}

/**
 * @brief  LPUART module wait to receive function
 * @param lpuartBase  LPUART number module
 * @param bufffer     the buffer to store receiving data
 * @param length      the length of receving data will be received
 * @param timeout     timeout value by miliseconds
 * @return this function retern the status code
 */
LPUART_receive_status Driver_LPUART_waitToReceive(lpuart_n lpuartBase, uint8_t* bufffer, const uint16_t length, const uint16_t timeout)
{
    LPUART_receive_status LPUART_Status_return = lpuart_waitToReceiveFaild;

    checkParameter(lpuartBase);
    if (receiveDataStructure[lpuartBase].status == LPUART_STATUS_IDLE)   /* if now the receiver is idle,set up the buffer and length and timeout for the new data farme */
    {
        receiveDataStructure[lpuartBase].LPUART_buffer = bufffer;        /* set receive buffer */
        receiveDataStructure[lpuartBase].LPUART_dataCount = 0;           /* reset count data variable */
        receiveDataStructure[lpuartBase].LPUART_length = length;         /* set length for the new farme data */
        HAL_LPUART_Read_DATA(basePtrLPUART[lpuartBase]);                 /* read data regsiter of LPUART module to clear data register befor receiving data */
        LPUART_ReceiveTimeout[lpuartBase] = timeout;                     /* set tiemeout for receiving */
        receiveDataStructure[lpuartBase].status = LPUART_STATUS_BUSY;    /* set receive state is busy */
        LPUART_Status_return = lpuart_waitToRecriveSuccess;              /* set status return is success */
        HAL_LPUART_Write_RIE(basePtrLPUART[lpuartBase], true);           /* enable receive interrupt */
    }

    return LPUART_Status_return;
}

/**
 * @brief  LPUART module wait to transmit function
 * @param lpuartBase  LPUART number module
 * @param bufffer     the buffer to store receiving data
 * @param length      the length of receving data will be received
 * @param timeout     timeout value by miliseconds
 * @return this function retern the status code
 */
LPUART_transmit_status Driver_LPUART_waitToTransmit(lpuart_n lpuartBase, uint8_t* bufffer, const uint16_t length, const uint16_t timeout)
{
    LPUART_transmit_status LPUART_Status_return = lpuart_waitToTransmitFaild;

    checkParameter(lpuartBase);
    if (transmitDataStructure[lpuartBase].status == LPUART_STATUS_IDLE)   /* if the transmit is free, set parameter for transmit */
    {
        transmitDataStructure[lpuartBase].LPUART_buffer = bufffer;        /* set transmit buffer */
        transmitDataStructure[lpuartBase].LPUART_dataCount = 0;           /* set count data variable */
        transmitDataStructure[lpuartBase].LPUART_length = length;         /* set the length for transmit farme */
        LPUART_TransmitTimeout[lpuartBase] = timeout;                     /* set the timeout for transmit */
        transmitDataStructure[lpuartBase].status = LPUART_STATUS_BUSY;    /* set transmit status is busy */
        LPUART_Status_return = lpuart_waitToTransmitSuccess;              /* set the return state is success */
        HAL_LPUART_Write_TIE(basePtrLPUART[lpuartBase], true);            /* enable transmit interrupt */
    }

    return LPUART_Status_return;
}

/**
 * @brief  LPUART0 interrupt handler
 * @param none
 * @return none
 */
void LPUART0_IRQHandler(void)
{
    /* check if interrupt occur because receive data is full */
   if (0 != HAL_LPUART_Read_RDRF(basePtrLPUART[mLPUART0]))    /* check receive data register full flag */
   {
        receiveDataStructure[mLPUART0].LPUART_buffer[receiveDataStructure[mLPUART0].LPUART_dataCount] = HAL_LPUART_Read_DATA(basePtrLPUART[mLPUART0]);    /* read receive data */
        receiveDataStructure[mLPUART0].LPUART_dataCount += 1;
        if (receiveDataStructure[mLPUART0].LPUART_dataCount == receiveDataStructure[mLPUART0].LPUART_length)    /* if receving data has finished */
        {
            LPUART_ReceiveTimeout[mLPUART0] = -1;                          /* disable timeout after receiving is success */
            HAL_LPUART_Write_RIE(basePtrLPUART[mLPUART0], false);          /* disable receive interrupt after read enough byte data */
            receiveDataStructure[mLPUART0].status = LPUART_STATUS_IDLE;    /* set receive running status is false to notice that receive is free */
            if (NULL != LPUART_ReceiveCallback[mLPUART0])                  /* if the receive callback function is not NULL, do this function */
            {
                LPUART_ReceiveCallback[mLPUART0]();
            }
        }
    }

    /* check if interrupt occur because trasmit data is empty */
    if((0 != HAL_LPUART_Read_TIE(basePtrLPUART[mLPUART0])) && (0 != (HAL_LPUART_Read_TDRE(basePtrLPUART[mLPUART0]))))    /* check transmit data register empty flag */
    {
        HAL_LPUART_Write_DATA(basePtrLPUART[mLPUART0], transmitDataStructure[mLPUART0].LPUART_buffer[transmitDataStructure[mLPUART0].LPUART_dataCount]);   /* send data from transmit buffer */
        transmitDataStructure[mLPUART0].LPUART_dataCount += 1;    /* increse data count */
        if (transmitDataStructure[mLPUART0].LPUART_dataCount == transmitDataStructure[mLPUART0].LPUART_length)    /* if sending data has finished */
        {
            LPUART_TransmitTimeout[mLPUART0] = -1;                          /* disable timeout after transmit data is success */
            transmitDataStructure[mLPUART0].status = LPUART_STATUS_IDLE;    /* set transmit status is free after send enough byte data */
            HAL_LPUART_Write_TIE(basePtrLPUART[mLPUART0], false);           /* disable transmit interrupt after send enough data byte */
            if (NULL != LPUART_TransmitCallback[mLPUART0])                  /* if the transmit callback function is not NULL, do this function */
            {
                LPUART_TransmitCallback[mLPUART0]();
            }
        }
    }
}

/**
 * @brief  LPUART1 interrupt handler
 * @param none
 * @return none
 */
void LPUART1_IRQHandler(void)
{
    /* check if interrupt occur because receive data is full */
   if (0 != HAL_LPUART_Read_RDRF(basePtrLPUART[mLPUART1]))    /* check receive data register full flag */
   {
        receiveDataStructure[mLPUART1].LPUART_buffer[receiveDataStructure[mLPUART1].LPUART_dataCount] = HAL_LPUART_Read_DATA(basePtrLPUART[mLPUART1]);    /* read receive data */
        receiveDataStructure[mLPUART1].LPUART_dataCount += 1;
        if (receiveDataStructure[mLPUART1].LPUART_dataCount == receiveDataStructure[mLPUART1].LPUART_length)    /* if receving data has finished */
        {
            LPUART_ReceiveTimeout[mLPUART1] = -1;                          /* disable timeout */
            HAL_LPUART_Write_RIE(basePtrLPUART[mLPUART1], false);          /* disable receive interrupt after read enough byte data */
            receiveDataStructure[mLPUART1].status = LPUART_STATUS_IDLE;    /* set receive running status is false to notice that receive is free */
            if (NULL != LPUART_ReceiveCallback[mLPUART1])                  /* if the receive callback function is not NULL, do this function */
            {
                LPUART_ReceiveCallback[mLPUART1]();
            }
        }
    }

    /* check if interrupt occur because trasmit data is empty */
    if((0 != HAL_LPUART_Read_TIE(basePtrLPUART[mLPUART1])) && (0 != (HAL_LPUART_Read_TDRE(basePtrLPUART[mLPUART1]))))    /* check transmit data register empty flag */
    {
        HAL_LPUART_Write_DATA(basePtrLPUART[mLPUART1], transmitDataStructure[mLPUART1].LPUART_buffer[transmitDataStructure[mLPUART1].LPUART_dataCount]);   /* send data from transmit buffer */
        transmitDataStructure[mLPUART1].LPUART_dataCount += 1;    /* increse data count */
        if (transmitDataStructure[mLPUART1].LPUART_dataCount == transmitDataStructure[mLPUART1].LPUART_length)    /* if sending data has finished */
        {
            LPUART_TransmitTimeout[mLPUART1] = -1;                          /* disable timeout after transmit data is success */
            transmitDataStructure[mLPUART1].status = LPUART_STATUS_IDLE;    /* set transmit status is free after send enough byte data */
            HAL_LPUART_Write_TIE(basePtrLPUART[mLPUART1], false);           /* disable transmit interrupt after send enough data byte */
            if (NULL != LPUART_TransmitCallback[mLPUART1])                  /* if the transmit callback function is not NULL, do this function */
            {
                LPUART_TransmitCallback[mLPUART1]();
            }
        }
    }
}

/**
 * @brief  LPUART2 interrupt handler
 * @param none
 * @return none
 */
void LPUART2_IRQHandler(void)
{
    /* check if interrupt occur because receive data is full */
   if (0 != HAL_LPUART_Read_RDRF(basePtrLPUART[mLPUART2]))    /* check receive data register full flag */
   {
        receiveDataStructure[mLPUART2].LPUART_buffer[receiveDataStructure[mLPUART2].LPUART_dataCount] = HAL_LPUART_Read_DATA(basePtrLPUART[mLPUART2]);    /* read receive data */
        receiveDataStructure[mLPUART2].LPUART_dataCount += 1;
        if (receiveDataStructure[mLPUART2].LPUART_dataCount == receiveDataStructure[mLPUART2].LPUART_length)    /* if receving data has finished */
        {
            LPUART_ReceiveTimeout[mLPUART2] = -1;                          /* disable timeout */
            HAL_LPUART_Write_RIE(basePtrLPUART[mLPUART2], false);          /* disable receive interrupt after read enough byte data */
            receiveDataStructure[mLPUART2].status = LPUART_STATUS_IDLE;    /* set receive running status is false to notice that receive is free */
            if (NULL != LPUART_ReceiveCallback[mLPUART2])                  /* if the receive callback function is not NULL, do this function */
            {
                LPUART_ReceiveCallback[mLPUART2]();
            }
        }
    }

    /* check if interrupt occur because trasmit data is empty */
    if((0 != HAL_LPUART_Read_TIE(basePtrLPUART[mLPUART2])) && (0 != (HAL_LPUART_Read_TDRE(basePtrLPUART[mLPUART2]))))    /* check transmit data register empty flag */
    {
        HAL_LPUART_Write_DATA(basePtrLPUART[mLPUART2], transmitDataStructure[mLPUART2].LPUART_buffer[transmitDataStructure[mLPUART2].LPUART_dataCount]);   /* send data from transmit buffer */
        transmitDataStructure[mLPUART2].LPUART_dataCount += 1;    /* increse data count */
        if (transmitDataStructure[mLPUART2].LPUART_dataCount == transmitDataStructure[mLPUART2].LPUART_length)    /* if sending data has finished */
        {
            LPUART_TransmitTimeout[mLPUART2] = -1;                          /* disable timeout after transmit data is success */
            transmitDataStructure[mLPUART2].status = LPUART_STATUS_IDLE;    /* set transmit status is free after send enough byte data */
            HAL_LPUART_Write_TIE(basePtrLPUART[mLPUART2], false);           /* disable transmit interrupt after send enough data byte */
            if (NULL != LPUART_TransmitCallback[mLPUART2])                  /* if the transmit callback function is not NULL, do this function */
            {
                LPUART_TransmitCallback[mLPUART2]();
            }
        }
    }
}
