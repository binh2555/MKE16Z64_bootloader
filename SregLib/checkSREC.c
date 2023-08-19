#include "checkSREC.h"
#include <stdbool.h>

/*******************************************************************************
* Definitions
******************************************************************************/
#define MAX_BUF_SIZE                      (80U)
#define COUNT_FEILD_START                 (2U)
#define MAX_SIZE_COUNT_FEILD              (2U)
#define MASK_SUM_ADDRESS_DATA             (0x00ffU)
#define CHECKSUM_START_POS(X)             (4 + (((X)-1) * 2))


/*******************************************************************************
 * Variable
*******************************************************************************/
static srecHandle s_statusStruct = {0};
uint8_t fileEnd = false;

/*******************************************************************************
* Prototypes
******************************************************************************/
static void handleBuff(const uint8_t* buff, srecHandle* s_statusStruct);
static bool handErr(const srecHandle statusCode, const uint8_t fileEnd);


uint8_t checkLine(uint8_t *buff)
{
    s_statusStruct.lineCount += 1;
    handleBuff(buff, &s_statusStruct);
    return handErr(s_statusStruct,fileEnd);
}

uint8_t convertHexCharToInterger(const uint8_t hexChar)
{
    uint8_t result = 16;
    if ((48 <= hexChar) && (57 >= hexChar))
    {
        result = hexChar - 48;
    }
    else if ((65 <= hexChar) && (70 >= hexChar))
    {
        result = hexChar - 55;
    }
    return result;
}

/*******************************************************************************
* function is used to handle the line data
* Paremeter:
        @buff : the buffer contain the line data
		@fData : the pointer point to the file storing data after it is checked 
		@s_statusStruct : the struct store informations of file
* Return: void
******************************************************************************/
static void handleBuff(const uint8_t* buff, srecHandle* s_statusStruct)
{
    uint8_t addressFeildStartPosition = 2;
    uint8_t countFeildValue = 0;
    uint8_t sumAddressAndData = 0;
    uint8_t checkSum = 0;
    uint8_t checksumDecimal = 0;
    uint8_t i = 0;
    
    countFeildValue = (convertHexCharToInterger(buff[2]) << 4) | convertHexCharToInterger(buff[3]);    /* get value of count feild in SREC line */

    /* get sum of address and data feild */
    for (i = 0; i < countFeildValue; i++)
    {
        checksumDecimal = (convertHexCharToInterger(buff[addressFeildStartPosition]) << 4) | convertHexCharToInterger(buff[addressFeildStartPosition+1]);
        addressFeildStartPosition += 2;
        sumAddressAndData += checksumDecimal;
    }
    sumAddressAndData = ~sumAddressAndData;    /* invert value to compare with checksum value */

    checkSum = (convertHexCharToInterger(buff[CHECKSUM_START_POS(countFeildValue)]) << 4) | convertHexCharToInterger(buff[CHECKSUM_START_POS(countFeildValue) + 1]);
    
    if (buff[0] == 83)    /* if the first character is 'S */
    {
        switch(buff[1])    /* check the second character */
        {
            case 48:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s0 += 1;
                break;
            case 49:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s1 += 1;
                break;
            case 50:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s2 += 1;
                break;
            case 51:
                s_statusStruct->s3 += 1;
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s3 += 1;
                break;
            case 52:
                s_statusStruct->s4 += 1;
                break;
            case 53:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s5 += 1;
                break;
            case 55:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s7 += 1;
                break;
            case 56:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s8 += 1;
                break;
            case 57:
                if (sumAddressAndData != checkSum)
                {
                    s_statusStruct->checkSumErr += 1;
                }
                s_statusStruct->s9 += 1;
                break;
            default:
                s_statusStruct->syntaxErr += 1;
                break;
        }
    }
    else
    {
        s_statusStruct->syntaxErr += 1;
    }
}

/*******************************************************************************
* function is used to handle if have any error happend
* Paremeter:
        @statusCode : the structer store all of informations of file
* Return: this function return the status flag
******************************************************************************/
static bool handErr(const srecHandle statusCode, const uint8_t fileEnd)
{
    bool returnFlag = true;
    
    if (1 <= statusCode.syntaxErr)
    {
        returnFlag = false;
    }
    
    if (1 <= statusCode.checkSumErr)
    {
        returnFlag = false;
    }
    
    if (1 < statusCode.s0)
    {
        returnFlag = false;
    }
    
    if (0 < statusCode.s4)
    {
        returnFlag = false;
    }
    
    if (1 <= statusCode.lineCountErr)
    {
        returnFlag = false;
    }
    
    if (1 <= statusCode.s1 && (0 < statusCode.s2 || 0 < statusCode.s3))
    {
        returnFlag = false;
    }
    else if (1 <= statusCode.s2 && (0 < statusCode.s3 || 0 < statusCode.s1))
    {
        returnFlag = false;
    }    
    else if (1 <= statusCode.s3 && (0 < statusCode.s2 || 0 < statusCode.s1))
    {
        returnFlag = false;
    }

    if (1 <= statusCode.s7 && (0 != statusCode.s8 || 0 != statusCode.s9))
    {
        returnFlag = false;
    }
    else if (1 <= statusCode.s8 && (0 != statusCode.s7 || 0 != statusCode.s9))
    {
        returnFlag = false;    
    }
    else if (1 <= statusCode.s9 && (0 != statusCode.s7 || 0 != statusCode.s8))
    {
        returnFlag = false;
    }
    return returnFlag;
}
