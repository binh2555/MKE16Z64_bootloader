#ifndef    _CHECK_SREC_H_
#define    _CHECK_SREC_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/*******************************************************************************
* Declaration
******************************************************************************/
/*
* Struction store status of SREC file
*/
typedef struct{
    uint8_t s0;     /* S0 */
    uint64_t s1;    /* S1 */
    uint64_t s2;    /* S2 */
    uint64_t s3;    /* S3 */
    uint64_t s4;    /* S4 */
    uint64_t s5;    /* S5 */
    uint64_t s7;    /* S7 */
    uint64_t s8;    /* S8 */
    uint64_t s9;    /* S9 */
    uint64_t lineCount;     /* count the number of line */
    uint8_t checkSumErr;    /* checksum error */
    uint8_t syntaxErr;      /* syntax error */
    uint8_t lineCountErr;   /* the number of line error */
}srecHandle;

/*******************************************************************************
* API
******************************************************************************/
uint8_t convertHexCharToInterger(const uint8_t hexChar);
uint8_t checkLine(uint8_t *buff);
#endif    /* _CHECK_SREC_H_ */


