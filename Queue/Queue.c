#include "Queue.h"
#include <stdio.h>

/*******************************************************************************
 * Definition
*******************************************************************************/
#define SIZE_OF_RXQUEUE       (4U)
#define SIZE_PER_RXELEMENT    (1024U)
#define SIZE_OF_TXQUEUE       (4U)
#define SIZE_PER_TXELEMENT    (64U)

/*******************************************************************************
 * Variable
*******************************************************************************/
static uint8_t s_queueRXBuff[SIZE_OF_RXQUEUE][SIZE_PER_RXELEMENT];    /* RXqueue buffer */
static uint8_t s_queueTXBuff[SIZE_OF_TXQUEUE][SIZE_PER_TXELEMENT];    /* TXqueue buffer */
static uint8_t s_pushTXIndex = 0;
static uint8_t s_popTXIndex = 0;
static uint8_t s_queueRXEleNum = 0;
static uint8_t s_queueTXEleNum = 0;

static uint8_t s_pushLineSREC = 3;
static uint8_t s_popLineSREC = 3;

/**
 * @brief  check RXqueue is empty or not
 * @param none
 * @return 0 if Rxqueue is empty,else return the number of SREC line in RXqueue
 */
uint8_t queueRXCheckEmpty(void)
{
    return s_queueRXEleNum;
}

uint8_t queueRXCheckFull(void)
{
    uint8_t result = 0;
    if (s_queueRXEleNum == SIZE_OF_RXQUEUE)
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  push data into RXqueue,if RXqueue is full,data will be overwritten
 * @param data    the data is pushed
 * @return none
 */
uint8_t* getRxQueueAddress(void)
{
    s_queueRXEleNum += 1;
    s_pushLineSREC = (s_pushLineSREC + 1) % SIZE_OF_RXQUEUE;
    return (&(s_queueRXBuff[s_pushLineSREC][0]));
}

/**
 * @brief  get SREC line in RXqueue
 * @param none
 * @return the starting address of SREC line
 */
uint8_t* RX_dequeue(void)
{
    s_queueRXEleNum -= 1;
    s_popLineSREC = (s_popLineSREC + 1) % SIZE_OF_RXQUEUE;
    return (&(s_queueRXBuff[s_popLineSREC][0]));
}


/**
 * @brief  check TXqueue is empty or not
 * @param none
 * @return 0 if Txqueue is empty,else return the number of SREC line in RXqueue
 */
uint8_t queueTXCheckEmpty(void)
{
    return s_queueTXEleNum;
}

uint8_t queueTXCheckFull(void)
{
    uint8_t result = 0;
    if (s_queueTXEleNum == SIZE_OF_TXQUEUE)
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  push data into TXqueue,if TXqueue is full,data will be overwritten
 * @param data    the data is pushed
 * @param sizeofOfData  the number of data
 * @return none
 */
void queueTXPush(const uint8_t* data, const uint16_t sizeOfData)
{
    uint16_t count = 0;
    while(count < sizeOfData)
    {
        s_queueTXBuff[s_pushTXIndex][count] = data[count];
        count++;
    }
    s_pushTXIndex = (s_pushTXIndex + 1) % SIZE_OF_TXQUEUE;
    s_queueTXEleNum += 1;
}

/**
 * @brief  get data in TXqueue
 * @param none
 * @return the data is got form TXqueue
 */
uint8_t* TX_dequeue(void)
{
    uint8_t* returnValue = NULL;
    if (0 != s_queueTXEleNum)
    {
        s_queueTXEleNum -= 1;
        returnValue = &(s_queueTXBuff[s_popTXIndex][0]);
    }
    s_popTXIndex = (s_popTXIndex + 1) % SIZE_OF_TXQUEUE;
    return returnValue;
}

