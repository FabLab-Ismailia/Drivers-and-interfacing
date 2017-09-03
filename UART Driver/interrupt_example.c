/*
This example to use uart interrupt 
it's recommended to use interrupt as the processor in the polling 
method asking the Uart module ? 
do you want any thing ? 
if the uart say no the processor go into a never ending loop 
of testing if the controller want to send or recieve any thing waiting the 
responsible flag to rise ,
but by using interrupt : 
at this time we can do a lot of things : use other modules like 
timers - counters - SPI - or any module of the controller , 
or even you can make the processor go to sleep 
to save power and wake him again when you want him , but before do that
you should go to datasheet to know the sleep modes and see each module in it
who is on during sleep and who can wake the processor if your module interrupt couldn't wake the processor
you can force it to wake by external interrupt .
*/

/*
in this example i use bluetooth module hc05
to test the code first in data sheet the : 
it's baud rate 9600 so >>> 
UART_init(9600); 
as the sender and reciver must work on the same baud rate and stop bits 
if you use different baud rate like 19200 the flag indicator only will 
flash very quickly and but the data won't send correctly . 
i send data from my android mobile using bluetooth terminal 
it's free application on google play >> then bluetooth module recive data 
and send it to the microcontroller via uart . 

*/

#include "micro_config.h"
volatile unsigned char recieved_data = 0 ; 
void UART_init (unsigned int baud) ; 
int main(void)
{   
	UART_init(9600); 
        DDRA =0xff ; 
   	DDRB |= (1<<PB0 ) |(1<<PB1) ; 
	sei();                                   // enable global interrupt 
	
  while(1)
       {   
	         if (recieved_data == '1')        PORTA |= 1<<PA0 ;    // led indicator 1
		 else if  (recieved_data == '2') PORTA |= 1<<PA1 ;    // led indicator 2
	         else if  (recieved_data == '3')	  PORTA |= 1<<PA2 ;   // led indicator 3 
		 else if(recieved_data == '4')    PORTA |= 1<<PA3 ;   // led indicator 4
		 else if (recieved_data == '5')   PORTA |= 1<<PA4 ;   // led indicator 5 		
	}
}

ISR (USART_RXC_vect)
{
recieved_data = UDR ; 	
PORTB ^= 1<<PB1 ;	                              // led indicator for recive flag 
}
