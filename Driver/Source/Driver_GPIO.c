#include "Driver_GPIO.h"

/**
 * @brief  write the value into a pin
 * @param :
 *          Port : the port name
 *          pin : the pin number
 *          value : 0(low) or 1(high)
 * @return none
 */
void Driver_WritePinDigital(mGpio_type Port, uint8_t pin, uint8_t value)
{
    switch (value)
    {
    case SET_VALUE:
        HAL_SetGPIO(Port, pin);
        break;
    case RESET_VALUE:
        HAL_ResetGPIO(Port, pin);
        break;
    default:
        while(1)
        {
            //doing something to notice that have a wrrong at here
        }
        break;
    }
}

/**
 * @brief  set input or output mode for pin
 * @param :
 *          Port : the port name
 *          pin : the pin number
 *          mode : 0(input mode) or 1(output mode)
 * @return none
 */
void Driver_SetPinMode(mGpio_type Port, uint8_t pin, uint8_t mode)
{
    HAL_GPIO_SetMode(Port, pin, mode);
}

/**
 * @brief  read data input pin
 * @param :
 *          Port : the port name
 *          pin : the pin number
 * @return 0(low) or 1(high)
 */
uint8_t Driver_ReadDataInput(mGpio_type Port, uint8_t pin)
{
    return (HAL_GPIO_ReadDataInput(Port, pin));
}


void Driver_TongglePin(mGpio_type gpio, uint8_t pin)
{
    HAL_TongglePin(gpio, pin);
}


/**
 * @brief  muxing mode for PB4
 * @param :
 *          Mode : muxing mode
 * @return none
 */
void Driver_Mux(mGpio_type port, uint8_t pin,Mux_mode Mode)
{
    HAL_Mux(port, pin, Mode);
}

/**
 * @brief  set IQR mode for GPIO pin
 * @param port : port of gpio pin
 * @param pin : pin number
 * @param mode : IRQ mode
 * @return none
 */
void Driver_ISRQMode(mGpio_type port, uint8_t pin, ISRQ_mode mode)
{
    HAL_ISRQMode(port, pin, mode);
}


/**
 * @brief  read and clear interrupt flag of pin
 * @param port : port of gpio pin
 * @param pin : pin number
 * @return return 1 if pin status is high, else return 0
 */
uint8_t Driver_ReadAndClearInterruptFlag(mGpio_type port, uint8_t pin)
{
    uint8_t statusFlag = 0;
    statusFlag = HAL_ReadInterruptFlag(port, pin);
    HAL_ClearInterruptFlag(port, pin);
    return statusFlag;
}

/**
 * @brief  clear interrupt flag of pin
 * @param port : port of gpio pin
 * @param pin : pin number
 * @return none
 */
void Driver_ClearInterruptFlag(mGpio_type port, uint8_t pin)
{
    HAL_ClearInterruptFlag(port, pin);
}

/**
 * @brief  write the value into PS feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void Driver_WritePSFeild(mGpio_type port, uint8_t pin, uint8_t value)
{
    HAL_WritePSFeild(port, pin, value);
}


/**
 * @brief  write the value into PE feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void Driver_WritePEFeild(mGpio_type port, uint8_t pin, uint8_t value)
{
    HAL_WritePEFeild(port, pin, value);
}

/**
 * @brief  register interrupt function for interrupt port B,C,D
 * @param  PortBCDFunc the poiter point to function will be called when interrput occur
 * @return none
 */
void Driver_IntPortBCDHandleFunc(void (*PortBCDFunc)(void))
{
    HAL_IntPortBCDHandleFunc(PortBCDFunc);
}
