/*
 * VoltageDetector.c
 *
 * Created: 2019-08-07 3:07:50 PM
 * Author : grant jones
 */ 

#include <avr/io.h>
#define F_CPU 20000000/6	//20MHz oscillator with a Div of 6
#include <util/delay.h>
#include <stdio.h>


int main(void)
{
    /* initialization of registers */
	//PORTA.DIRSET = 0x20;	//sets PIN5 as output (not sure of needed)
	PORTA.IN = 0xDF;		//sets all pins to be inputs except for PIN5
	ADC0.CTRLA |= 0x01;		//enables ADC
	ADC0.CTRLC |= 0x10;		//sets ADC reference to VCC
	ADC0.INTCTRL = 0x01;	//sets write interrupt
	
	float ADC_Result = 0;	//ADC raw output
	float Voltage = 0;		//ADC voltage adjusted to readable value
	float Voltage_Current_Sensor = 0;		//ADC voltage output from current sensor adjusted to readable value

	//uint8_t loop_flag = 1;

    while (1) 
    {
		//LED ON
		PORTA.PIN5CTRL = 0x08;  //enables pull up for PIN4 (LED)
		
		ADC0.MUXPOS = 0x04;		//sets which pin gets the analog signal (PIN4)
		ADC0.COMMAND |= 0x01;	//begins single time conversion
			while (ADC0.COMMAND == 0x01){}
		ADC_Result = ADC0.RES;	//high and low bytes of 10 bit result
		Voltage = ADC_Result*5/1023;
		ADC_Result = -1;
		_delay_ms(1000);
		
		
		//LED OFF
		PORTA.PIN5CTRL &= 0x00;  //disables pull up for PIN4
		
		ADC0.MUXPOS = 0x02;			//sets which pin gets the analog signal (PIN4)
		ADC0.COMMAND |= 0x01;		//begins single time conversion
			while (ADC0.COMMAND == 0x01){}
		ADC_Result = ADC0.RES;	//high and low bytes of 10 bit result
		Voltage_Current_Sensor = ADC_Result*5/1023;
		ADC_Result = -1;
		//_delay_ms(1000);
		

		
		
    }
}

