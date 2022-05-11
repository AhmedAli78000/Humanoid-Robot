#include <stdint.h>
#include "C:/Keil/Labware/inc/tm4c123gh6pm.h"
//#include "C:/Keil/EE319Kware/ADCSWTrigger_4C123/PLL.h"
void SystemInit (){}
//one channel	
void ADC_initialize(){
	uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x10;
	delay=0;
	SYSCTL_RCGCADC_R |= 0x0001;
	delay = 0;
	GPIO_PORTE_AFSEL_R |= 0x10;     // 3) enable alternate function on PE4
	GPIO_PORTE_DEN_R &= ~0x10;      // 4) disable digital I/O on PE4
	GPIO_PORTE_AMSEL_R |= 0x10;     // 5) enable analog functionality on PE4
	ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
	ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
	ADC0_SSMUX3_R &= ~0x000F;       // 11) clear SS3 field
	ADC0_SSMUX3_R += 9;             //    set channel
	ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;           // 13) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3
	
	
}
void adc_intialize_2_channels(){
	uint32_t delay;
	SYSCTL_RCGCADC_R |= 0x0001;
	delay=0;
	ADC0_ACTSS_R &= ~0x0001;        // 9) disable sample sequencer 0
	ADC0_EMUX_R &= ~0x0000F;         // 10) seq3 is software trigger
	ADC0_SSMUX0_R &= ~0x00FF;       //clear sample input select
	ADC0_SSMUX0_R |= 0x00000021; 	  // select Ain 0 & Ain2 for first sample and second 
	ADC0_SSCTL0_R =  0x00000010;         // 12) no TS1 D0, yes IE0 END1
	// not completed yet 
}
	


uint32_t ADC0_InSeq3(void){  uint32_t result;
  ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
    // if you have an A0-A3 revision number, you need to add an 8 usec wait here
  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result

	ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
  return result;
}


int __main()
	{
	
	uint32_t data;
	ADC_initialize();
	
	while(1){
		data=ADC0_InSeq3();
	}
	
	
	
}
