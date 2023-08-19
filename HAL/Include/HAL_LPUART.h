#ifndef _HAL_LPUART_H_
#define _HAL_LPUART_H_

#include "MKE16Z4.h"
#include "stdint.h"


/******************************************************************
 * API
******************************************************************/

/**
 * @brief  write to TE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_TE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to RE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_RE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to RIE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to RIE feild
 * @return none
 */
void HAL_LPUART_Write_RIE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to TIE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TIE feild
 * @return none
 */
void HAL_LPUART_Write_TIE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  Read Transmit interrupt enable bit of LPUART module
 * @param base    LPUART base address
 * @return 0 if transmit interrupt is disable,else return 1
 */
uint8_t HAL_LPUART_Read_TIE(LPUART_Type* const base);

/**
 * @brief  write to M10 feild in LPUART Baud Register
 * @param const base    LPUART const base address
 * @param value   the value write to M10 feild
 * @return none
 */
void HAL_LPUART_Write_M10(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to OSR feild in LPUART Baud Register
 * @param const base    LPUART const base address
 * @param value   the value write to OSR feild
 * @return none
 */
void HAL_LPUART_Write_OSR(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to SBR feild in LPUART Baud Register
 * @param const base    LPUART const base address
 * @param value   the value write to SBR feild
 * @return none
 */
void HAL_LPUART_Write_SBR(LPUART_Type* const base, const uint16_t value);

/**
 * @brief  write to M7 feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_M7(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to M feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_M(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to PE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to PE feild
 * @return none
 */
void HAL_LPUART_Write_PE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to parity type feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to PT feild,0 = even parity, 1  = odd parity
 * @return none
 */
void HAL_LPUART_Write_PT(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to MSBF feild in LPUART Status Register
 * @param const base    LPUART const base address
 * @param value   the value write to MSBF feild
 * @return none
 */
void HAL_LPUART_Write_MSBF(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to SBNS feild in LPUART Status Register
 * @param const base    LPUART const base address
 * @param value   the value write to SBNS feild
 * @return none
 */
void HAL_LPUART_Write_SBNS(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to TE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_RXFE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  write to TXFE feild in LPUART Control Register
 * @param const base    LPUART const base address
 * @param value   the value write to TXFE feild
 * @return none
 */
void HAL_LPUART_Write_TXFE(LPUART_Type* const base, const uint8_t value);

/**
 * @brief  read to RDRF feild in LPUART Stauts Register
 * @param const base    LPUART const base address
 * @param value   the value write to RDRF feild
 * @return none
 */
uint8_t HAL_LPUART_Read_RDRF(LPUART_Type* const base);

/**
 * @brief  read to TRDE feild in LPUART Status Register
 * @param const base    LPUART const base address
 * @return 0 or 1
 */
uint8_t HAL_LPUART_Read_TDRE(LPUART_Type* const base);

/**
 * @brief  read DATA register
 * @param const base    LPUART const base address
 * @return 0 or 1
 */
uint8_t HAL_LPUART_Read_DATA(LPUART_Type* const base);

/**
 * @brief  write to DATA register
 * @param const base    LPUART const base address
 * @param value   the value write to TRDE feild
 * @return none
 */
void HAL_LPUART_Write_DATA(LPUART_Type* const base, const uint8_t value);



#endif    /* _HAL_LPUART_H_ */
/***************************************************
 * END OF HAL_LPUART.H FILE
 **************************************************/