#ifndef PWM_H_
#define PWM_H_
/****************************************************/
/*Notes:
**PWM frequency of 2 outputs connected to the same block generator -> must be equal , because the block generator have one value of load then on value 
of PWM frequency for the 2 pins connected to it .
**frequency of PWM = ( frequency of MCU / prescalar ) * (1 / load) .
**output frequency of PWM can be changed to any value by changing thr #define below .
*/
/****************************************************/
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
/****************************************************/
/*Types
typedef unsigned int  uint32_t ;
typedef unsigned char uint8_t ;
*/
/***************************************************/
#define F_CPU 16000000    //16MHz
#define F_PWM 50          //50Hz
/***************************************************/
typedef enum{
	NO_PRESCALAR = 1 , PRESCALAR_2 = 2 , PRESCALAR_4 = 4 , PRESCALAR_8 = 8 , PRESCALAR_16 = 16 , PRESCALAR_32 = 32 , PRESCALAR_64 = 64
}PRESCALAR;

/***************************************************/
/*function prototypes*/
void PWM_init(uint8_t port , uint8_t pin , PRESCALAR prescalar , float duty_cycle);
uint32_t Port_to_Base(uint8_t port);

#endif