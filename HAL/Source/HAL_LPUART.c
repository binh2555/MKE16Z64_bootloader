#include "HAL_LPUART.h"
#include <stdio.h>
#include <stdbool.h>

/******************************************************************
 * Definition
******************************************************************/

/* LPUART Control Register */
#define LPUART_TE_MASK               (0xFFF7FFFFU)
#define LPUART_TE_SHIFT              (19U)
#define LPUART_TE_W(X,Y)             (((X) & LPUART_TE_MASK) | (Y << LPUART_TE_SHIFT))

#define LPUART_RE_MASK               (0xFFFBFFFFU)
#define LPUART_RE_SHIFT              (18U)
#define LPUART_RE_W(X,Y)             (((X) & LPUART_RE_MASK) | (Y << LPUART_RE_SHIFT))

#define LPUART_M7_MASK               (0xFFFFF7FFU)
#define LPUART_M7_SHIFT              (11U)
#define LPUART_M7_W(X,Y)             (((X) & LPUART_M7_MASK) | (Y << LPUART_M7_SHIFT))

#define LPUART_M_MASK                (0xFFFFFFEFU)
#define LPUART_M_SHIFT               (4U)
#define LPUART_M_W(X,Y)              (((X) & LPUART_M_MASK) | (Y << LPUART_M_SHIFT))

#define LPUART_PE_MASK               (0xFFFFFFFDU)
#define LPUART_PE_SHIFT              (1U)
#define LPUART_PE_W(X,Y)             (((X) & LPUART_PE_MASK) | (Y << LPUART_PE_SHIFT))

#define LPUART_PT_MASK               (0xFFFFFFFEU)
#define LPUART_PT_SHIFT              (0U)
#define LPUART_PT_W(X,Y)             (((X) & LPUART_PT_MASK) | (Y << LPUART_PT_SHIFT))

#define LPUART_RIE_MASK              (0xFFDFFFFFU)
#define LPUART_RIE_SHIFT             (21U)
#define LPUART_RIE_W(X,Y)            (((X) & LPUART_RIE_MASK) | (Y << LPUART_RIE_SHIFT))

#define LPUART_TIE_MASK              (0xFF7FFFFFU)
#define LPUART_TIE_SHIFT             (23U)
#define LPUART_TIE_W(X,Y)            (((X) & LPUART_TIE_MASK) | (Y << LPUART_TIE_SHIFT))

/* LPUART Baud Rate Register */
#define LPUART_M10_MASK              (0xDFFFFFFFU)
#define LPUART_M10_SHIFT             (29U)
#define LPUART_M10_W(X,Y)            (((X) & LPUART_M10_MASK) | (Y << LPUART_M10_SHIFT))

#define LPUART_SBNS_MASK             (0xFFFFDFFFU)
#define LPUART_SBNS_SHIFT            (13U)
#define LPUART_SBNS_W(X,Y)           (((X) & LPUART_SBNS_MASK) | (Y << LPUART_SBNS_SHIFT))

#define LPUART_OSR_MASK              (0xE0FFFFFFU)
#define LPUART_OSR_SHIFT             (24U)
#define LPUART_OSR_W(X,Y)            (((X) & LPUART_OSR_MASK) | (Y << LPUART_OSR_SHIFT))

#define LPUART_SBR_MASK              (0xFFFFE000U)
#define LPUART_SBR_SHIFT             (0U)
#define LPUART_SBR_W(X,Y)            (((X) & LPUART_SBR_MASK) | (Y << LPUART_SBR_SHIFT))

#define LPUART_RDRF_SHIFT            (21U)
#define LPUART_TDRE_SHIFT            (23U)

/* LPUART Status Register */
#define LPUART_MSBF_MASK             (0xDFFFFFFFU)
#define LPUART_MSBF_SHIFT            (29U)
#define LPUART_MSBF_W(X,Y)           (((X) & LPUART_MSBF_MASK) | (Y << LPUART_MSBF_SHIFT))


/* LPUART FIFO Register */
#define LPUART_RXFE_MASK             (0xFFFFFFF7U)
#define LPUART_RXFE_SHIFT            (3U)
#define LPUART_RXFE_W(X,Y)           (((X) & LPUART_RXFE_MASK) | (Y << LPUART_RXFE_SHIFT))

#define LPUART_TXFE_MASK             (0xFFFFFF7FU)
#define LPUART_TXFE_SHIFT            (7U)
#define LPUART_TXFE_W(X,Y)           (((X) & LPUART_TXFE_MASK) | (Y << LPUART_TXFE_SHIFT))



/***************************************************************************************
 * Variable
****************************************************************************************/
LPUART_Type * basePtrLPUART[] = LPUART_BASE_PTRS;           /* LPUART base address peripheral array */



/***************************************************************************************
 * API
****************************************************************************************/
/**
 * @brief  write to TE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_TE(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_TE_W(base->CTRL, value);
}

/**
 * @brief  write to RE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_RE(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_RE_W(base->CTRL, value);
}

/**
 * @brief  write to RIE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to RIE feild
 * @return none
 */
void HAL_LPUART_Write_RIE(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_RIE_W(base->CTRL, value);
}

/**
 * @brief  write to TIE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TIE feild
 * @return none
 */
void HAL_LPUART_Write_TIE(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_TIE_W(base->CTRL, value);
}

/**
 * @brief  Read Transmit interrupt enable bit of LPUART module
 * @param base    LPUART base address
 * @return 0 if transmit interrupt is disable,else return 1
 */
uint8_t HAL_LPUART_Read_TIE(LPUART_Type* const base)
{
    uint8_t result = 0;
    if (base->CTRL & (1 << LPUART_TIE_SHIFT))
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  write to M10 feild in LPUART Baud Register
 * @param base    LPUART base address
 * @param value   the value write to M10 feild
 * @return none
 */
void HAL_LPUART_Write_M10(LPUART_Type* const base, const uint8_t value)
{
    base->BAUD = LPUART_M10_W(base->BAUD, value);
}

/**
 * @brief  write to OSR feild in LPUART Baud Register
 * @param base    LPUART base address
 * @param value   the value write to OSR feild
 * @return none
 */
void HAL_LPUART_Write_OSR(LPUART_Type* const base, const uint8_t value)
{
    base->BAUD = LPUART_OSR_W(base->BAUD, value);
}

/**
 * @brief  write to SBR feild in LPUART Baud Register
 * @param base    LPUART base address
 * @param value   the value write to SBR feild
 * @return none
 */
void HAL_LPUART_Write_SBR(LPUART_Type* const base, const uint16_t value)
{
    base->BAUD = LPUART_SBR_W(base->BAUD, value);
}

/**
 * @brief  write to M7 feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_M7(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_M7_W(base->CTRL, value);
}

/**
 * @brief  write to M feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_M(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_M_W(base->CTRL, value);
}

/**
 * @brief  write to PE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to PE feild
 * @return none
 */
void HAL_LPUART_Write_PE(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_PE_W(base->CTRL, value);
}

/**
 * @brief  write to parity type feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to PT feild,0 = even parity, 1  = odd parity
 * @return none
 */
void HAL_LPUART_Write_PT(LPUART_Type* const base, const uint8_t value)
{
    base->CTRL = LPUART_PT_W(base->CTRL, value);
}

/**
 * @brief  write to MSBF feild in LPUART Status Register
 * @param base    LPUART base address
 * @param value   the value write to MSBF feild
 * @return none
 */
void HAL_LPUART_Write_MSBF(LPUART_Type* const base, const uint8_t value)
{
    base->STAT = LPUART_MSBF_W(base->STAT, value);
}

/**
 * @brief  write to SBNS feild in LPUART Status Register
 * @param base    LPUART base address
 * @param value   the value write to SBNS feild
 * @return none
 */
void HAL_LPUART_Write_SBNS(LPUART_Type* const base, const uint8_t value)
{
    base->BAUD = LPUART_SBNS_W(base->BAUD, value);
}

/**
 * @brief  write to TE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TE feild
 * @return none
 */
void HAL_LPUART_Write_RXFE(LPUART_Type* const base, const uint8_t value)
{
    base->FIFO = LPUART_RXFE_W(base->FIFO, value);
}

/**
 * @brief  read to RDRF feild in LPUART Stauts Register
 * @param base    LPUART base address
 * @return 0 or 1
 */
uint8_t HAL_LPUART_Read_RDRF(LPUART_Type* const base)
{
    uint8_t result = 0;
    if ((base->STAT & (1 << LPUART_RDRF_SHIFT)) != 0)
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  read to TRDE feild in LPUART Status Register
 * @param base    LPUART base address
 * @return 0 or 1
 */
uint8_t HAL_LPUART_Read_TDRE(LPUART_Type* const base)
{
    uint8_t result = 0;
    if ((base->STAT & (1 << LPUART_TDRE_SHIFT)) != 0)
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  read DATA register
 * @param base    LPUART base address
 * @return 0 or 1
 */
uint8_t HAL_LPUART_Read_DATA(LPUART_Type* const base)
{
    return (const uint8_t)base->DATA;
}

/**
 * @brief  write to DATA register
 * @param base    LPUART base address
 * @param value   the value write to TRDE feild
 * @return none
 */
void HAL_LPUART_Write_DATA(LPUART_Type* const base, const uint8_t value)
{
    base->DATA = value;
}

/**
 * @brief  write to TXFE feild in LPUART Control Register
 * @param base    LPUART base address
 * @param value   the value write to TXFE feild
 * @return none
 */
void HAL_LPUART_Write_TXFE(LPUART_Type* const base, const uint8_t value)
{
    base->FIFO = LPUART_TXFE_W(base->FIFO, value);
}



