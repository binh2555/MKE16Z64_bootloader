#include "HAL_GPIO.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/
FGPIO_Type * mPort[] = FGPIO_BASE_PTRS;    /* base address FGPIO array */
PORT_Type * portAddress[] = PORT_BASE_PTRS;    /* base address port array */

/*******************************************************************************
 * Prototype
 ******************************************************************************/
static void checkGPIO(mGpio_type gpio);
static void (*IntPortBCDhandleFunc)(void) = NULL;    /* the pointer contain the address of function will be called when interrput occur */

/**
 * @brief  check gpio is valid or invalid
 * @param  gpio gpio will be checked
 * @return none
 */
static void checkGPIO(mGpio_type gpio)
{
    if ((gpio >= END_OF_GPIO_NUMBER) | (0 > gpio))
    {
        while(1)
        {
            //doing something to notice that have a error at here
        }
    }
}

/**
 * @brief  set pin in portB
 * @param : 
 *          pin : pin number
 * @return none
 */
void HAL_SetGPIO(mGpio_type gpio, uint8_t pin)
{
    checkGPIO(gpio);
    mPort[gpio]->PSOR |= (1 << pin);
}

/**
 * @brief  reset pin in portB
 * @param : 
 *          pin : pin number
 * @return none
 */
void HAL_ResetGPIO(mGpio_type gpio, uint8_t pin)
{
    checkGPIO(gpio);
    mPort[gpio]->PCOR |= (1 << pin);
}

/**
 * @brief  set input or output mode for a pin in gpioB
 * @param : 
 *          pin : pin number
 *          mode : input or outpur mode
 * @return none
 */
void HAL_GPIO_SetMode(mGpio_type gpio, uint8_t pin, uint8_t mode)
{
    checkGPIO(gpio);
    mPort[gpio]->PDDR = ((mPort[gpio]->PDDR & (~(1 << pin))) | (mode << pin));
}

/**
 * @brief  read data in a pin of gpioB
 * @param : 
 *          pin : pin number
 * @return : the value of corresponding pin
 */
uint8_t HAL_GPIO_ReadDataInput(mGpio_type gpio, uint8_t pin)
{
    uint8_t result = 0;
    if ((mPort[gpio]->PDIR & (1 << pin)) != 0)
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  toggle output pin
 * @param :
 *          pin : pin number
 * @return : none
 */
void HAL_TongglePin(mGpio_type gpio, uint8_t pin)
{
    mPort[gpio]->PTOR |= (1 << pin);
}

/**
 * @brief  Set muxing mode for GPIOB pin 4
 * @param  Mode of gpio pin
 * @return none
 */
void HAL_Mux(mGpio_type port, uint8_t pin,Mux_mode Mode)
{
    checkGPIO(port);
    portAddress[port]->PCR[pin] = ((portAddress[port]->PCR[pin] & MUX_MASK) | MUX_PC(Mode));
}

/**
 * @brief  Set ISRQ for GPIOB pin 3
 * @param  Mode of gpio pin
 * @return none
 */
void HAL_ISRQMode(mGpio_type port, uint8_t pin,ISRQ_mode Mode)
{
    checkGPIO(port);
    portAddress[port]->PCR[pin] = (portAddress[port]->PCR[pin] & ISRQ_MASK ) | (ISRQ_PC(Mode));
}


/**
 * @brief  clear interrupt flag in port D
 * @param  pin pin number
 * @return none
 */
void HAL_ClearInterruptFlag(mGpio_type port, uint8_t pin)
{
    checkGPIO(port);
    portAddress[port]->ISFR |= (1 << pin); 
}

/**
 * @brief  read interrupt flag in port D
 * @param  pin pin number
 * @return none
 */
uint8_t HAL_ReadInterruptFlag(mGpio_type port, uint8_t pin)
{
    uint8_t result = 0;
    checkGPIO(port);
    if ((portAddress[port]->ISFR & (1 << pin)) != 0)
    {
        result = 1;
    }
    return result;
}

/**
 * @brief  write the value into PS feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void HAL_WritePSFeild(mGpio_type port, uint8_t pin, uint8_t value)
{
    portAddress[port]->PCR[pin] = ((portAddress[port]->PCR[pin] & PS_MASK) | PS_PC(value));
}

/**
 * @brief  write the value into PE feild of PCD2
 * @param  value the value which will be written
 * @return none
 */
void HAL_WritePEFeild(mGpio_type port, uint8_t pin, uint8_t value)
{
    portAddress[port]->PCR[pin] = ((portAddress[port]->PCR[pin] & PE_MASK) | PE_PC(value));
}

/**
 * @brief  register interrupt function for interrupt port B,C,D
 * @param  PortBCDFunc the poiter point to function will be called when interrput occur
 * @return none
 */
void HAL_IntPortBCDHandleFunc(void (*PortBCDFunc)(void))
{
    IntPortBCDhandleFunc = PortBCDFunc;
}

/**
 * @brief  interrupt services funtion for Port B,C,D interrupt
 * @param  None
 * @return none
 */
void PORTBCD_IRQHandler(void)
{
    HAL_ClearInterruptFlag(GPIO_D, 2);
    if (NULL != IntPortBCDhandleFunc)
    {
        IntPortBCDhandleFunc();
    }
}
