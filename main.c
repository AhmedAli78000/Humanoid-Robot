#include "GPIO.h"
#include "PWM.h"

void main(){
	PIN_CONFIG pwm_pin ;
  pwm_pin.data_dir = OUTPUT ;
  pwm_pin.alternative_fun = ENABLE ;
  pwm_pin.mode = DIGITAL ;
  pwm_pin.resistor_type = NO_PULL ;
	GPIO_init_pin ('B' , 6 , &pwm_pin);
	PWM_init('B' , 6 , NO_PRESCALAR , 0.065);
	while(1);
}