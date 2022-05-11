include "UART.h"

void UART0_init(void){
	SYSCTL_RCGCUART_R |= 0x00000001;   //enable clk for UART0
	SYSCTL_RCGCGPIO_R |= 0x00000001;   //enable clk for Port A
	UART0_CTL_R &= ~(0x00000001);     //disable UART0
	
	/*configuration of uart0 : baud rate and control and status registers */
	//baud rate = 9600 bit/sec
	UART0_IBRD_R = 104;     // IBRD = int(16,000,000/(16*9600)) = int(104.1666667)
  UART0_FBRD_R = 11;     // FBRD = round(0.1666667 * 64) = 11
	UART0_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs

  UART0_CTL_R |= 0x00000301;     // enable UART0 and TX and RX
	
	//set pin 0,1 in port A to uart alt.Function
	GPIO_PORTA_LOCK_R = 0x4C4F434B ;
	GPIO_PORTA_CR_R = 0x03 ;
	GPIO_PORTF_DIR_R |= 0x02 ;
	GPIO_PORTA_AFSEL_R |= 0x03;    // enable alt funct on PA0-1
	GPIO_PORTA_DEN_R |= 0x03;      
	// configure Pa0-1 as UART0
	GPIO_PORTA_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFFFFF00)+0x00000011;
	GPIO_PORTA_AMSEL_R &= ~(0x03);   // disable analog on PA0-1
}


uint8_t UART0_read(void){
	while((UART0_FR_R&0x0010) != 0);      // wait until RXFE is 0
	return((uint8_t)(UART0_DR_R&0xFF));
}

void UART0_write(uint8_t data){
	while((UART0_FR_R&0x0020) != 0);     // wait until TXFF is 0
  UART0_DR_R = data;
}
