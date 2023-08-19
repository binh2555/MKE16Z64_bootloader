#ifndef    _HAL_GPIO_H_
#define    _HAL_GPIO_H_

#include <stdint.h>
#include <stdio.h>
#include "MKE16Z4.h"
#include "header.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MUX_MASK            (0xFFFFF8FFU)
#define MUX_SHIFT           (8U)
#define MUX_PC(x)           (x << MUX_SHIFT)

#define ISRQ_MASK           (0xFFF0FFFFU)
#define ISRQ_SHIFT          (16U)
#define ISRQ_PC(X)          (X << ISRQ_SHIFT)

#define PS_MASK             (0xFFFFFFFEU)
#define PS_SHIFT            (0U)
#define PS_PC(X)            (X << PS_SHIFT)

#define PE_MASK             (0xFFFFFFFDU)
#define PE_SHIFT            (1U)
#define PE_PC(X)            (X << PS_SHIFT)

 /* typedef enum for muxing mode */
typedef enum{
    MUX_DISABLE_MODE = 0,    /* Disable mode = 0 */
    MUX_GPIO_MODE = 1,            /* Gpio mode = 1 */
    MUX_ALT2_MODE = 2        /* ALT2 mode = 2 */
}Mux_mode;

typedef enum{
    ISRQ_Disable = 0,
    ISRQ_FallingEdge = 10
}ISRQ_mode;

typedef enum{
    PORTBCD_IQR = 26
}IQRnumber_type;

/**
 * @brief  Set muxing mode for GPIOB pin 4
 * @param  Mode of gpio pin
 * @return none
 */
void HAL_Mux(mGpio_type port, uint8_t pin,Mux_mode Mode);



/**
 * @brief  Set ISRQ for GPIOB pin 3
 * @param  Mode of gpio pin
 * @return none
 */
void HAL_ISRQMode(mGpio_type port, uint8_t pin,ISRQ_mode Mode);


/**
 * @brief  clear interrupt flag in port D
 * @param  pin pin number
 * @return none
 */
void HAL_ClearInterruptFlag(mGpio_type port, uint8_t pin);

/**
 * @brief  read interrupt flag in port D
 * @param  pin pin number
 * @return none
 */
uint8_t HAL_ReadInterruptFlag(mGpio_type port, uint8_t pin);

/**
 * @brief  write the value into PS feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void HAL_WritePSFeild(mGpio_type port, uint8_t pin, uint8_t value);

/**
 * @brief  write the value into PE feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void HAL_WritePEFeild(mGpio_type port, uint8_t pin, uint8_t value);

/**
 * @brief  register interrupt function for interrupt port B,C,D
 * @param  PortBCDFunc the poiter point to function will be called when interrput occur
 * @return none
 */
void HAL_IntPortBCDHandleFunc(void (*PortBCDFunc)(void));

/**
 * @brief  set pin in portB
 * @param : 
 *          pin : pin number
 * @return none
 */
void HAL_SetGPIO(mGpio_type gpio, uint8_t pin);

/**
 * @brief  reset pin in portB
 * @param : 
 *          pin : pin number
 * @return none
 */
void HAL_ResetGPIO(mGpio_type gpio, uint8_t pin);

/**
 * @brief  set input or output mode for a pin in gpioB
 * @param : 
 *          pin : pin number
 *          mode : input or outpur mode
 * @return none
 */
void HAL_GPIO_SetMode(mGpio_type gpio, uint8_t pin, uint8_t mode);

/**
 * @brief  read data in a pin of gpioB
 * @param : 
 *          pin : pin number
 * @return : the value of corresponding pin
 */
uint8_t HAL_GPIO_ReadDataInput(mGpio_type gpio, uint8_t pin);

/**
 * @brief  toggle output pin
 * @param :
 *          pin : pin number
 * @return : none
 */
void HAL_TongglePin(mGpio_type gpio, uint8_t pin);

#endif    /* _HAL_GPIO_H_ */
