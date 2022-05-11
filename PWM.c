#include "PWM.h"

void PWM_init(uint8_t port , uint8_t pin , PRESCALAR prescalar , float duty_cycle){
	if( ((port == 'B') && (pin > 3)) || (((port == 'E')|| (port == 'C')) && ((pin == 4) || (pin == 5))) ){ /*pins for PWM0 module*/
		SYSCTL_RCGCPWM_R |= (1<<0) ; /*enable clock for PWM0*/
		
		/*select alternative fun as pWM0*/
		uint32_t base = Port_to_Base(port) ;
		GPIO_PORT_PCTL(base) = (GPIO_PORT_PCTL(base) & ((0xffffffff) ^ ((0x0000000f)<<(4*pin)))) | ((0b0100)<<(4*pin));
	
		if(prescalar == NO_PRESCALAR){  /*prescalar setting*/
			SYSCTL_RCC_R &= ~(1<<20);     //clear USEPWMDIV in RCC reg
		}
		else{
			SYSCTL_RCC_R |= (1<<20);      //to enable prescalar
			switch(prescalar){            //according to desired divisor , put values in PWMDIV field in RCC reg. 
				case PRESCALAR_2  : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) ;
                            break ;
				case PRESCALAR_4  : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (1<<17) ;
                            break ;
				case PRESCALAR_8  : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (2<<17) ;
                            break ;
				case PRESCALAR_16 : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (3<<17) ;
                            break ;
				case PRESCALAR_32 : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (4<<17) ;
                            break ;
				case PRESCALAR_64 : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (7<<17) ;
                            break ;
				
			}
		}
		
		/*Configure the PWM generator for countdown mode with immediate updates to the parameters.*/
		if(port == 'B' && (pin == 6 || pin == 7)){         //pwm 0 generator 0
			PWM0_0_CTL_R = 0 ; 
		}
		else if(port == 'B' && (pin == 4 || pin == 5)){    //pwm 0 generator 1
			PWM0_1_CTL_R = 0 ;
		}
		else if(port == 'E' && (pin == 4 || pin == 5)){    //pwm 0 generator 2
			PWM0_2_CTL_R = 0 ;
		}
		else if(port == 'C' && (pin == 4 || pin == 5)){    //pwm 0 generator 3
			PWM0_3_CTL_R = 0 ;
		}
		/*PWM generation form : set high at reload , set low at match*/
		if(port == 'B'){
			if(pin == 6){
				PWM0_0_GENA_R = 0x0000008C ;      
			}
			else if(pin == 7){
				PWM0_0_GENB_R = 0x0000080C ;
			}
		}
		if(port == 'B'){
			if(pin == 4){
				PWM0_1_GENA_R = 0x0000008C ;
			}
			else if(pin == 5){
				PWM0_1_GENB_R = 0x0000080C ;
			}
		}
		if(port == 'E'){
			if(pin == 4){
				PWM0_2_GENA_R = 0x0000008C ;
			}
			else if(pin == 5){
				PWM0_2_GENB_R = 0x0000080C ;
			}
		}
		if(port == 'C'){
			if(pin == 4){
				PWM0_3_GENA_R = 0x0000008C ;
			}
			else if(pin == 5){
				PWM0_3_GENB_R = 0x0000080C ;
			}
		}
		
		/*set load (the value at which counter will re-count , defined by user through the formula given in PWM.h*/
		uint32_t load = (F_CPU / prescalar) / F_PWM ;    //calculation of load value
		if(port == 'B' && (pin == 6 || pin == 7)){
			PWM0_0_LOAD_R = load ; 
		}
		else if(port == 'B' && (pin == 4 || pin == 5)){
			PWM0_1_LOAD_R = load ; 
		}
		else if(port == 'E' && (pin == 4 || pin == 5)){
			PWM0_2_LOAD_R = load ; 
		}
		else if(port == 'C' && (pin == 4 || pin == 5)){
			PWM0_3_LOAD_R = load ; 
		}
		
		/*set compare match value*/
		uint32_t compare_value  = (1 - duty_cycle) * load ;    //calculation of compare value
		if(port == 'B'){
			if(pin == 6){
				PWM0_0_CMPA_R = compare_value ;  
			}
			else if(pin == 7){
				PWM0_0_CMPB_R = compare_value ;
			}
		}
		if(port == 'B'){
			if(pin == 4){
				PWM0_1_CMPA_R = compare_value ;
			}
			else if(pin == 5){
				PWM0_1_CMPB_R = compare_value ;
			}
		}
		if(port == 'E'){
			if(pin == 4){
				PWM0_2_CMPA_R = compare_value ;
			}
			else if(pin == 5){
				PWM0_2_CMPB_R = compare_value ;
			}
		}
		if(port == 'C'){
			if(pin == 4){
				PWM0_3_CMPA_R = compare_value ;
			}
			else if(pin == 5){
				PWM0_3_CMPB_R = compare_value ;
			}
		}
		
		/*start timer*/
		if(port == 'B' && (pin == 6 || pin == 7)){
			PWM0_0_CTL_R = 0x00000001 ; 
		}
		else if(port == 'B' && (pin == 4 || pin == 5)){
			PWM0_1_CTL_R = 0x00000001 ;
		}
		else if(port == 'E' && (pin == 4 || pin == 5)){
			PWM0_2_CTL_R = 0x00000001 ;
		}
		else if(port == 'C' && (pin == 4 || pin == 5)){
			PWM0_3_CTL_R = 0x00000001 ;
		}
		
		/*enable PWM output*/
		if(port == 'B'){
			if(pin == 6){
				PWM0_ENABLE_R |= (1<<0) ;     /*enable M0PWM0*/
			}
			else if(pin == 7){
				PWM0_ENABLE_R |= (1<<1) ;     /*enable M1PWM0*/
			}
		}
		if(port == 'B'){
			if(pin == 4){
				PWM0_ENABLE_R |= (1<<2) ;    /*enable M2PWM0*/
			}
			else if(pin == 5){
				PWM0_ENABLE_R |= (1<<3) ;    /*enable M3PWM0*/
			}
		}
		if(port == 'E'){
			if(pin == 4){
				PWM0_ENABLE_R |= (1<<4) ;    /*enable M4PWM0*/
			}
			else if(pin == 5){
				PWM0_ENABLE_R |= (1<<5) ;   /*enable M5PWM0*/
			}
		}
		if(port == 'C'){
			if(pin == 4){
				PWM0_ENABLE_R |= (1<<6) ;   /*enable M6PWM0*/
			}
			else if(pin == 5){   
				PWM0_ENABLE_R |= (1<<7) ;   /*enable M7PWM0*/
			}
		}
	}
  else if(((port == 'F') && (pin < 4)) || ((port == 'A') && ((pin == 6) || (pin == 7))) || ((port == 'D') && (pin < 2))){ /*pins for PWM1 module*/
    SYSCTL_RCGCPWM_R |= (1<<1) ; /*enable clock for PWM0*/
		
		/*select alternative fun as pWM0*/
	  uint32_t base = Port_to_Base(port) ;
		GPIO_PORT_PCTL(base) = (GPIO_PORT_PCTL(base) & ((0xffffffff) ^ ((0x0000000f)<<(4*pin)))) | ((0b0101)<<(4*pin));
	
		if(prescalar == NO_PRESCALAR){  /*prescalar setting*/
			SYSCTL_RCC_R &= ~(1<<20);
		}
		else{
			SYSCTL_RCC_R |= (1<<20);
			switch(prescalar){
				case PRESCALAR_2  : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) ;
                            break ;
				case PRESCALAR_4  : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (1<<17) ;
                            break ;
				case PRESCALAR_8  : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (2<<17) ;
                            break ;
				case PRESCALAR_16 : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (3<<17) ;
                            break ;
				case PRESCALAR_32 : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (4<<17) ;
                            break ;
				case PRESCALAR_64 : SYSCTL_RCC_R = (SYSCTL_RCC_R & (~(7<<17))) | (7<<17) ;
                            break ;
				
			}
		}
		
		/*Configure the PWM generator for countdown mode with immediate updates to the parameters.*/
		if(port == 'D' && (pin == 0 || pin == 1)){
			PWM1_0_CTL_R = 0 ; 
		}
		else if(port == 'A' && (pin == 6 || pin == 7)){
			PWM1_1_CTL_R = 0 ;
		}
		else if(port == 'F' && (pin == 0 || pin == 1)){
			PWM1_2_CTL_R = 0 ;
		}
		else if(port == 'F' && (pin == 2 || pin == 3)){
			PWM1_3_CTL_R = 0 ;
		}
		/*PWM generation form : set high at reload , set low at match*/
		if(port == 'D'){
			if(pin == 0){
				PWM1_0_GENA_R = 0x0000008C ; 
			}
			else if(pin == 1){
				PWM1_0_GENB_R = 0x0000080C ;
			}
		}
		if(port == 'A'){
			if(pin == 6){
				PWM1_1_GENA_R = 0x0000008C ;
			}
			else if(pin == 7){
				PWM1_1_GENB_R = 0x0000080C ;
			}
		}
		if(port == 'F'){
			if(pin == 0){
				PWM1_2_GENA_R = 0x0000008C ;
			}
			else if(pin == 1){
				PWM1_2_GENB_R = 0x0000080C ;
			}
			else if(pin == 2){
				PWM1_3_GENA_R = 0x0000008C ;
			}
			else if(pin == 3){
				PWM1_3_GENB_R = 0x0000080C ;
			}
		}
		
		/*set load (the value at which counter will re-count , defined by user through the formula given in PWM.h*/
		uint32_t load = (F_CPU / prescalar) / F_PWM ;    //calculation of load value
		
		if(port == 'D' && (pin == 0 || pin == 1)){
			PWM1_0_LOAD_R = load ; 
		}
		else if(port == 'A' && (pin == 6 || pin == 7)){
			PWM1_1_LOAD_R = load ; 
		}
		else if(port == 'F' && (pin == 0 || pin == 1)){
			PWM1_2_LOAD_R = load ; 
		}
		else if(port == 'F' && (pin == 2 || pin == 3)){
			PWM1_3_LOAD_R = load ; 
		}
		
		/*set compare match value*/
		uint32_t compare_value  = (1 - duty_cycle) * load ;
		if(port == 'D'){
			if(pin == 0){
				PWM1_0_CMPA_R = compare_value ; 
			}
			else if(pin == 1){
				PWM1_0_CMPB_R = compare_value ;
			}
		}
		if(port == 'A'){
			if(pin == 6){
				PWM1_1_CMPA_R = compare_value ;
			}
			else if(pin == 7){
				PWM1_1_CMPB_R = compare_value ;
			}
		}
		if(port == 'F'){
			if(pin == 0){
				PWM1_2_CMPA_R = compare_value ;
			}
			else if(pin == 1){
				PWM1_2_CMPB_R = compare_value ;
			}
			else if(pin == 2){
				PWM1_3_CMPA_R = compare_value ;
			}
			else if(pin == 3){
				PWM1_3_CMPB_R = compare_value ;
			}
		}
		
		/*start timer*/
		if(port == 'D' && (pin == 0 || pin == 1)){
			PWM1_0_CTL_R = 1 ; 
		}
		else if(port == 'A' && (pin == 6 || pin == 7)){
			PWM1_1_CTL_R = 1 ;
		}
		else if(port == 'F' && (pin == 0 || pin == 1)){
			PWM1_2_CTL_R = 1 ;
		}
		else if(port == 'F' && (pin == 2 || pin == 3)){
			PWM1_3_CTL_R = 1 ;
		}
		
		/*enable PWM output*/
		if(port == 'D'){
			if(pin == 0){
				PWM1_ENABLE_R |= (1<<0) ;     /*enable M0PWM1*/
			}
			else if(pin == 1){
				PWM1_ENABLE_R |= (1<<1) ;     /*enable M1PWM1*/
			}
		}
		if(port == 'A'){
			if(pin == 6){
				PWM1_ENABLE_R |= (1<<2) ;    /*enable M2PWM1*/
			}
			else if(pin == 7){
				PWM1_ENABLE_R |= (1<<3) ;    /*enable M3PWM1*/
			}
		}
		if(port == 'F'){
			if(pin == 0){
				PWM1_ENABLE_R |= (1<<4) ;    /*enable M4PWM1*/
			}
			else if(pin == 1){
				PWM1_ENABLE_R |= (1<<5) ;   /*enable M5PWM1*/
			}
			else if(pin == 3){
				PWM1_ENABLE_R |= (1<<6) ;   /*enable M6PWM1*/
			}
			else if(pin == 4){   
				PWM1_ENABLE_R |= (1<<7) ;   /*enable M7PWM1*/
			}
		}
	}
}

uint32_t Port_to_Base(uint8_t port){
	uint32_t base = 0 ;
	switch(port){
		case 'A' : base = BASE_A ; 
							 break ;
		case 'B' : base = BASE_B ; 
							 break ;
		case 'C' : base = BASE_C ; 
							 break ;
		case 'D' : base = BASE_D ; 
							 break ;
		case 'E' : base = BASE_E ; 
							 break ;
		case 'F' : base = BASE_F ; 
							 break ;
	}
	return base ;
}

