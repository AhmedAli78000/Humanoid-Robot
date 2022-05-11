#ifndef GPIO_H_
#define GPIO_H_

#include "tm4c123gh6pm.h"
/************************************************/
//MACROS
#define GPIO_PORT_LOCK(base)      (*((volatile uint32_t *)(base+GPIO_LOCK_OFFSET)))
#define GPIO_PORT_CR_R(base)      (*((volatile uint32_t *)(base+GPIO_COMMIT_OFFSET)))
#define GPIO_PORT_AFSEL(base)     (*((volatile uint32_t *)(base+GPIO_ALTERNATE_FUNC_SEL_OFFSET)))
#define GPIO_PORT_DIR(base)       (*((volatile uint32_t *)(base+GPIO_DIRECTION_OFFSET)))
#define GPIO_PORT_DEN(base)       (*((volatile uint32_t *)(base+GPIO_DIGITAL_EN_OFFSET)))
#define GPIO_PORT_AMSEL(base)     (*((volatile uint32_t *)(base+GPIO_ANALOG_MODE_SEL_OFFSET)))
#define GPIO_PORT_PUR(base)       (*((volatile uint32_t *)(base+GPIO_PULL_UP_SEL_OFFSET)))
#define GPIO_PORT_PDR(base)       (*((volatile uint32_t *)(base+GPIO_PULL_DOWN_SEL_OFFSET)))
#define GPIO_PORT_DATA(base)      (*((volatile uint32_t *)(base+GPIO_DATA_OFFSET)))
/*************************************************/
//Types
typedef unsigned int  uint32_t ;
typedef unsigned char uint8_t ;

/*************************************************/
#define BASE_A 0x40004000
#define BASE_B 0x40005000
#define BASE_C 0x40006000
#define BASE_D 0x40007000
#define BASE_E 0x40024000
#define BASE_F 0x40025000
/******************/
#define GPIO_DATA_OFFSET                   0x3FC
#define GPIO_DIRECTION_OFFSET              0x400
#define GPIO_ALTERNATE_FUNC_SEL_OFFSET     0x420
#define GPIO_PULL_UP_SEL_OFFSET            0x510
#define GPIO_PULL_DOWN_SEL_OFFSET          0x514
#define GPIO_DIGITAL_EN_OFFSET             0x51C
#define GPIO_LOCK_OFFSET                   0x520
#define GPIO_COMMIT_OFFSET                 0x524
#define GPIO_ANALOG_MODE_SEL_OFFSET        0x528
#define GPIO_PORT_CONTROL_OFFSET           0x52C
#define GPIO_ADC_CONTROL_OFFSET            0x530
#define GPIO_DMA_CONTROL_OFFSET            0x534
#define GPIO_PERIPHRAL_ID_4_OFFSET         0xFD0
#define GPIO_PERIPHRAL_ID_5_OFFSET         0xFD4
#define GPIO_PERIPHRAL_ID_6_OFFSET         0xFD8
#define GPIO_PERIPHRAL_ID_7_OFFSET         0xFDC
#define GPIO_PERIPHRAL_ID_0_OFFSET         0xFE0
#define GPIO_PERIPHRAL_ID_1_OFFSET         0xFE4
#define GPIO_PERIPHRAL_ID_2_OFFSET         0xFE8
#define GPIO_PERIPHRAL_ID_3_OFFSET         0xFEC
#define GPIO_PRIMECELL_ID_0_OFFSET         0xFF0
#define GPIO_PRIMECELL_ID_1_OFFSET         0xFF4
#define GPIO_PRIMECELL_ID_2_OFFSET         0xFF8
#define GPIO_PRIMECELL_ID_3_OFFSET         0xFFC
/********************************************************/
typedef enum{
	INPUT = 1 , OUTPUT
}DATA_DIR;

typedef enum{
	DIGITAL = 1 , ANALOG
}MODE;

typedef enum{
	ENABLE = 1 , DISABLE
}AILERNATIVE_FUN;

typedef enum{
	PULL_UP = 1 , PULL_DOWN
}RESIStOR_TYPE;

typedef enum{
  PASS = 1 , INCORRECT_PORT , INCORRECT_PIN
}ERROR_TYPE;

typedef enum{
	LOW = 0 , HIGH
}DATA;

typedef struct{
	DATA_DIR data_dir ;
	MODE mode ;
	AILERNATIVE_FUN alternative_fun ;
	RESIStOR_TYPE resistor_type ;
}PIN_CONFIG;
/**********************************************************/
//function prototypes
ERROR_TYPE init_pin (uint32_t base , uint32_t pin , PIN_CONFIG * config);
ERROR_TYPE write_pin (uint32_t base , uint32_t pin , DATA data);
ERROR_TYPE read_pin (uint32_t base , uint32_t pin , DATA *data);

#endif