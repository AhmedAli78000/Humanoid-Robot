#include "GPIO.h"

ERROR_TYPE init_pin (uint32_t base , uint32_t pin , PIN_CONFIG * config){
	ERROR_TYPE state = PASS ;
	
	if(base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D || base == BASE_E || base == BASE_F){
		if((base == BASE_E && pin > 5) || (base == BASE_C && pin > 3) || (base == BASE_F && pin > 4) || (pin > 7)){
			state = INCORRECT_PIN ;
		}
		else{
//enable clock
     	switch(base){
    		case BASE_A : SYSCTL_RCGCGPIO_R |= (0x01) ;
							    		break ;
	    	case BASE_B : SYSCTL_RCGCGPIO_R |= (0x02) ;
		    							break ;
	    	case BASE_C : SYSCTL_RCGCGPIO_R |= (0x04) ;
	    								break ;
	    	case BASE_D : SYSCTL_RCGCGPIO_R |= (0x08) ;
	    								break ;
	    	case BASE_E : SYSCTL_RCGCGPIO_R |= (0x10) ;
	    								break ;
	    	case BASE_F : SYSCTL_RCGCGPIO_R |= (0x20) ;
	    								break ;
	}
//dummy variable to ensure clk in steadystate
	   uint8_t x = 0 ;
	   x++ ;
//remove lock and commit
	   if(base != BASE_C){
      	GPIO_PORT_LOCK(base) = 0x4C4F434B ;
	}
   	GPIO_PORT_CR_R(base) |= (1<<pin) ;
	
//use alternative function or not
  	if(config->alternative_fun == ENABLE){
	  	GPIO_PORT_AFSEL(base) |= (1<<pin) ;
	}
	  else if(config->alternative_fun == DISABLE){
	  	GPIO_PORT_AFSEL(base) &= ~(1<<pin) ;
	}
	
//data direction 
  	if(config->data_dir == INPUT){
  		GPIO_PORT_DIR(base) &= ~(1<<pin) ;
	}
	  else if(config->data_dir == OUTPUT){
	  	GPIO_PORT_DIR(base) |= (1<<pin) ;
	}
	
//determine digital or analogue mode
	  if(config->mode == DIGITAL){
	  	GPIO_PORT_DEN(base) |= (1<<pin) ;
	  	GPIO_PORT_AMSEL(base) &= ~(1<<pin) ;
	}
	  if(config->mode == ANALOG){
	  	GPIO_PORT_AMSEL(base) |= (1<<pin) ;
	  	GPIO_PORT_DEN(base) &= ~(1<<pin) ;
	}
		
//pull up or pull down
	  if(config->resistor_type == PULL_UP){
	  	GPIO_PORT_PUR(base) |= (1<<pin) ;
			GPIO_PORT_PDR(base) &= ~(1<<pin) ;
		}
		if(config->resistor_type == PULL_DOWN){
	  	GPIO_PORT_PDR(base) |= (1<<pin) ;
			GPIO_PORT_PUR(base) &= ~(1<<pin) ;
		}
}
}
	else{
		state = INCORRECT_PORT ;
	}
	return state ;
}

ERROR_TYPE write_pin (uint32_t base , uint32_t pin , DATA data){
	ERROR_TYPE state = PASS ;
	if(base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D || base == BASE_E || base == BASE_F){
		if((base == BASE_E && pin > 5) || (base == BASE_C && pin > 3) || (base == BASE_F && pin > 4) || (pin > 7)){
			state = INCORRECT_PIN ;
		}
		else{
			GPIO_PORT_DATA(base) = (GPIO_PORT_DATA(base) & ~(1<<pin)) | (data<<pin) ;
		}
	}
	else{
		state = INCORRECT_PORT ;
	}
	return state ;
}

ERROR_TYPE read_pin (uint32_t base , uint32_t pin , DATA *data){
	ERROR_TYPE state = PASS ;
	if(base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D || base == BASE_E || base == BASE_F){
		if((base == BASE_E && pin > 5) || (base == BASE_C && pin > 3) || (base == BASE_F && pin > 4) || (pin > 7)){
			state = INCORRECT_PIN ;
		}
		else{
			*data = (((GPIO_PORT_DATA(base) & (1<<pin)))>>pin) ;
		}
	}
	else{
		state = INCORRECT_PORT ;
	}
	return state ;
}