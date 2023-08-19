#include "Driver_Clock.h"
#include "Driver_GPIO.h"
#define DELAY_CNT               (3000000)
#define LED_PIN                 (4U)
#define LED_PORT                (GPIO_B)

void initLed();
void delay();

void user_main(void)
{
    initLed();

    while (1)
    {
        delay();
        /* Toggle LEDs */
        Driver_TongglePin(LED_PORT, LED_PIN);
    }
}

void initLed()
{
    /* Enable Clock for PORTB */
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    Driver_EnableGPIOBClock();
    
    /* set LED pin as GPIO */
    Driver_Mux(LED_PORT, LED_PIN, MUX_GPIO_MODE);
    Driver_SetPinMode(LED_PORT, LED_PIN, OUTPUT_MODE);
    
    /* Set default value LED pin = HIGH */
    Driver_WritePinDigital(LED_PORT, LED_PIN, 1);
}

void delay()
{
    uint32_t i;
    for (i = 0; i < DELAY_CNT; i++)
    {
        __asm("nop");
    }
}
