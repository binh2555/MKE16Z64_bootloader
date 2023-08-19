#ifndef _HEADER_H_
#define _HEADER_H_

/*******************************************************************************
* Definitions Port_type
******************************************************************************/

/* define GPIO number */
#ifndef _MPORT_TYPE_
#define _MPORT_TYPE_
typedef enum{
    GPIO_A = 0,
    GPIO_B = 1,
    GPIO_C = 2,
    GPIO_D = 3,
    END_OF_GPIO_NUMBER
}mGpio_type;
#endif    /* _PORT_TYPE_ */

#endif    /* _HEADER_H_ */

