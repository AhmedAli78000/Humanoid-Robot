#ifndef UART_H_
#define UART_H_

#include "tm4c123gh6pm.h"
#include "stdint.h"

/*NOTES :
*assume system clock : 16MHZ
*/

/*Types
typedef unsigned int  uint32_t ;
typedef unsigned char uint8_t ;
*/

//function prototypes
void UART0_init(void);
uint8_t UART0_read(void);
void UART0_write(uint8_t data);

#endif