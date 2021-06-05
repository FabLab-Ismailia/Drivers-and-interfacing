/*
Uart programming tiva c   Arm uC 
/* **************************************************************************
        desired clk = SysClk / (16*clkDiv )  -> SysClk = 16 Mhz 
        Sysclk / 16 = 1 Mhz 
   so  desired clk = 1Mhz / clkDiv           
         
  example : 
  if desired baud rate = 9600 
  clkDiv = 1000 000 / 9600 = 104.166667 
  then to obtain intValue cast this alue  intBaudRate = (int) clkDiv 
  fractionBaudRate = ((clkDiv - (float)intBaudRate) * 64 ) + 0.5  ;
  then cast fraction value to be able to put it in fraction baud rate register
  work with baud rates : 2400 - 4800 - 9600 - 57600 - 115200 - 230400 - 250 000 :) 
  /***********************/
  /**** MOHAMMED HEMED ***/
  /******************************************************************************/
#include "tm4c123gh6pm.h"
#include <math.h>
#define clk  16000000UL				// not used just to tell user the freq of this code  
void uart_init(int baud)
{   
        float clkDiv ;          			 	// clkDiv to hold clock divisor  
        float fractionBaudRate ;  			 	// fractionBaudRate to hold fraction part    	
	int intBaudRate ;  				 	// intBaudRate to hold int part             				
        clkDiv = (float)(1000000.0 / baud) ; 		 	// cast sum of two integers (float) 
        intBaudRate = (int) clkDiv ; 			 	// cast clkDiv to obtain integer value
        fractionBaudRate = clkDiv - (float)intBaudRate ; 	// cast integer Value  
        fractionBaudRate = ((fractionBaudRate * 64.0) + 0.5) ; 	// equation from data sheet for fraction value 
        
        SYSCTL_RCGCUART_R |= 1 ; 			// provide clk to uart0 
	SYSCTL_RCGCGPIO_R |= 1 ; 			// enable clk to portA	
	
	UART0_CTL_R  = 0 ; 				// disable uart during set config
	UART0_LCRH_R = 0x60; 				// FRAME = 8byte - one stop bit - no parity  
	UART0_IBRD_R = intBaudRate ;
  	UART0_FBRD_R = (int) fractionBaudRate ; 	/* cast the float value to (int) to be able to put in register */ 	  
	UART0_CTL_R  = 0x301	;			// Enable uart  - TXE - RXE 
	UART0_CC_R = 0 ; 				// use system clk source   

	GPIO_PORTA_DEN_R |= 0x03 ;  				// Enable Digital i/o 		 
	GPIO_PORTA_AFSEL_R |= 0x03 ;  			// Enable Alternate function 
    	GPIO_PORTA_PCTL_R  |= 0x11 ;  			// using uart funcion in pins A0 - A1 
}

void uart_send (char tx_data)
{
//while (UART0-> FR & 0x80 != 1)	; 		// wait until tx buffer become empty 
while ((UART0_FR_R & 0X20)) ; 				// or :  wait until tx buffer not full 
UART0_DR_R = tx_data ; 
}


char uart_receive (void)
{
char rx_data ; 
while ((UART0_FR_R & 0x10) != 0) ; 				// wait until rx buffer is not empty 
rx_data =  UART0_DR_R ; 						// read rx_data before be volatile 
return rx_data ;   							
}

void delay_ms(int delay_ms) 
{
long int delay_time = 3180 *  delay_ms ; 
while (-- delay_time) ; 
} 

int main()
{
  /* i use 250 000 baud rate as example you can choose your appropraite baud rate :) */	
  uart_init (250000) ; 
  while (1) 
  {
  delay_ms(1000) ; 
  uart_send ('g') ; 
  delay_ms(1000) ;
  }
}
