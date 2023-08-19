#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

/**
 * @brief  push data into RXqueue
 * @param data    the data is pushed
 * @return none
 */
uint8_t* getRxQueueAddress(void);

/**
 * @brief  get SREC line in RXqueue
 * @param none
 * @return the starting address of SREC line
 */
uint8_t* RX_dequeue(void);

/**
 * @brief  check RXqueue is empty or not
 * @param none
 * @return 0 if Rxqueue is empty,else return the number of SREC line in RXqueue
 */
uint8_t queueRXCheckEmpty(void);

uint8_t queueRXCheckFull(void);

/**
 * @brief  check TXqueue is empty or not
 * @param none
 * @return 0 if Txqueue is empty,else return the number of SREC line in RXqueue
 */
uint8_t queueTXCheckEmpty(void);

uint8_t queueTXCheckFull(void);

/**
 * @brief  push data into TXqueue
 * @param data    the data is pushed
 * @param sizeofOfData  the number of data
 * @return none
 */
void queueTXPush(const uint8_t* data, const uint16_t sizeOfData);

/**
 * @brief  get data in TXqueue
 * @param none
 * @return the data is got form TXqueue
 */
uint8_t* TX_dequeue(void);


#endif    /* _QUEUE_H_ */
/*******************************************************************
 * END OF QUEUE.h FILE!!!
 ******************************************************************/
