#include <stdint.h>
#include "C:/Keil/Labware/inc/tm4c123gh6pm.h"

/*
	Theory
	The TM4C123GH6PM ADC module features 12-bit conversion resolution and supports 12 input
	channels, plus an internal temperature sensor. Each ADC module contains four programmable
	sequencers allowing the sampling of multiple analog input sources without controller intervention.
	Each sample sequencer provides flexible programming with fully configurable input source, trigger
	events, interrupt generation, and sequencer priority. In addition, the conversion value can optionally
	be diverted to a digital comparator module. Each ADC module provides eight digital comparators.
	Each digital comparator evaluates the ADC conversion value against its two user-defined values to
	determine the operational range of the signal. The trigger source for ADC0 and ADC1 may be
	independent or the two ADC modules may operate from the same trigger source and operate on
	the same or different inputs. A phase shifter can delay the start of sampling by a specified phase
	angle. When using both ADC modules, it is possible to configure the converters to start the
	conversions coincidentally or within a relative phase from each other
*/
/*
 * Example on how to use
 *int __main()
	{
		uint32_t pins[11]={0,2,3,4,5,6,1,0,1,9,1};
		uint32_t data[11];
		ADC_initialize(pins,11,1);
		
		while(1){
		ADC_readChannels(data,11);
			
		}
  }
 *@pins : array of pins to be intialized
 *@data : array which will contain data
*/


void adc0_intialize_n_channels(uint32_t pins[],uint32_t number_of_channels , _Bool sample); //ADC0
void adc1_intialize_n_channels(uint32_t pins[],uint32_t number_of_channels , _Bool sample); //ADC1

/*
 *	@brief : function intializes ADC0 but with a limit on number of channels as adc0 can only sample 8 channels maximum
 
 *  @pins : an array of integar contain adc pin numbers 
    for example of array contains 9 , 2 
		pin name will be PE4 & PE2 will be intialized as ADC pins respectively

		@number_of_channels :number of channels to be intialized = size of pins array
		@sample : bool value determines if adc will average reading or not if its enabled 
							then 64 consecutive ADC samples are averaged to generate one result in 
							the sequencer FIFO
		       ***************************
						pin number ||	  pin  name	 
		       ***************************
              Ain 0    ||    PE3
						  Ain 1		 ||		 PE2
				      Ain 2		 ||		 PE1
				      Ain 3		 ||    PE0
				      Ain 4		 || 	 PD3
				      Ain 5		 ||    PD2
				      Ain 6		 ||    PD1
				      Ain 7		 ||    PD0
				      Ain 8		 ||    PE5
				      Ain 9		 ||    PE4
				      Ain 10	 ||	   PB4
				      Ain 11	 ||    PB5
						 
		from datasheet page 801				 
*/
void ADC0_InSeq0(uint32_t *result,uint32_t size);
void ADC1_InSeq0(uint32_t *result,uint32_t size);
/*
 *@brief : function reads value sampled by adc from FIFO by the order of the pins arranged in array(pins)
 *
 *@result: an array passed  by refrence to function adc reading will be included in that array
 *@size  : size of array result 
*/
void ADC_initialize(uint32_t pins[],uint32_t number_of_channels , _Bool sample);

/*
 *@brief : same adc0_intialize_n_channels and adc1_intialize_n_channels but it can initialize up to the 12 channels that exist
 *				 in ADC  as it will use both adc0 and adc1 	
*/
void ADC_readChannels(uint32_t *data,uint32_t number_of_channels);

/*
 * @brief : it is used with ADC_initialize as it reads up to 12 reading from both adc0 and adc1 together
 *
 */









