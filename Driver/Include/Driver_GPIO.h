#ifndef    _DRIVER_GPIO_H
#define    _DRIVER_GPIO_H

#include "HAL_GPIO.h"

/*******************************************************************************
* Definition
******************************************************************************/
#define SET_VALUE    (1U)
#define RESET_VALUE  (0U)

#define INPUT_MODE       (0U)
#define OUTPUT_MODE      (1U)

/*******************************************************************************
* API
******************************************************************************/
/**
 * @brief  write the value into a pin
 * @param :
 *          Port : the port name
 *          pin : the pin number
 *          value : 0(low) or 1(high)
 * @return none
 */
void Driver_WritePinDigital(mGpio_type Port, uint8_t pin, uint8_t value);

/**
 * @brief  set input or output mode for pin
 * @param :
 *          Port : the port name
 *          pin : the pin number
 *          mode : 0(input mode) or 1(output mode)
 * @return none
 */
void Driver_SetPinMode(mGpio_type Port, uint8_t pin, uint8_t mode);

/**
 * @brief  read data input pin
 * @param :
 *          Port : the port name
 *          pin : the pin number
 * @return 0(low) or 1(high)
 */
uint8_t Driver_ReadDataInput(mGpio_type Port, uint8_t pin);

void Driver_TongglePin(mGpio_type gpio, uint8_t pin);

/**
 * @brief  muxing mode for PB4
 * @param :
 *          Mode : muxing mode
 * @return none
 */
void Driver_Mux(mGpio_type port, uint8_t pin,Mux_mode Mode);

/**
 * @brief  set IQR mode for GPIO pin
 * @param port : port of gpio pin
 * @param pin : pin number
 * @param mode : IRQ mode
 * @return none
 */
void Driver_ISRQMode(mGpio_type port, uint8_t pin, ISRQ_mode mode);

/**
 * @brief  read and clear interrupt flag of pin
 * @param port : port of gpio pin
 * @param pin : pin number
 * @return return 1 if pin status is high, else return 0
 */
uint8_t Driver_ReadAndClearInterruptFlag(mGpio_type port, uint8_t pin);

/**
 * @brief  clear interrupt flag of pin
 * @param port : port of gpio pin
 * @param pin : pin number
 * @return none
 */
void Driver_ClearInterruptFlag(mGpio_type port, uint8_t pin);

/**
 * @brief  write the value into PS feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void Driver_WritePSFeild(mGpio_type port, uint8_t pin, uint8_t value);

/**
 * @brief  write the value into PE feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void Driver_WritePEFeild(mGpio_type port, uint8_t pin, uint8_t value);

/**
 * @brief  register interrupt function for interrupt port B,C,D
 * @param  PortBCDFunc the poiter point to function will be called when interrput occur
 * @return none
 */
void Driver_IntPortBCDHandleFunc(void (*PortBCDFunc)(void));

#endif    /* _DRIVER_GPIO_H */
/********************************************************************************
 *END FILE!!!
 ********************************************************************************/
