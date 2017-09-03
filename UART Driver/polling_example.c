/*
This is example to use the library 
by polling .
*/

/*
We have two microcontrollers : 
micro 1 >> sender 
micro 2 >> reciver
*/

/********************************
micro 1 code 
*********************************/

#include "UART.h"

int main(void)
{   
	uart_init(9600) ;
	  
	
    while(1)
    {
        uart_send_byte('a') ;
    }
}
/***************************************************************/

/********************************
micro 2 code 
*********************************/

#include "UART.h"
#define ON    'a'
#define OFF   'b'
int main(void)
{  
	DDRD |= (1<<PD6) |(1<<PD5) | (1<<PD4)  ;  
	unsigned char data = 0 ;
	uart_init(9600); 
	
    while(1)
    {
    data = uart_rec_byte() ; 
	
	 if (data == ON )
	{
	PORTD |= 1<<PD6 ; 
	}  
     else if (data == OFF)     
     {
	 
    	PORTD &= ~(1<<PD6)  ;
      }
    }
}
















