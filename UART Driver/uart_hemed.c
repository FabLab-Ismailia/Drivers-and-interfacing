

/*
my uart library :) 


*/
#include "uart_hemed.h"
void UART_init (unsigned int baud)
{
	unsigned int UBBR  ;
	/*
	baud rate configuration :
	lrint is a function to approximiate the number 
	*/
	UBBR = lrint(F_CPU / (8L * baud)) -1  ; 
	UBRRH = (unsigned char)(UBBR>>8);
	UBRRL = (unsigned char)UBBR;
	/*Double speed mode */
	UCSRA |= (1<<U2X) ; 
	/*Enable Rx - Tx - Enable interrupt */
	UCSRB |=(1<<RXCIE) |(1<<TXCIE)|(1<<UDRIE)|(1<<RXEN)|(1<<TXEN) ;
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
}



void uart_send_byte (const unsigned char byte) {

while (!(UCSRA & (1<<TXC))) ; 
UDR = byte ; 

} 

unsigned char uart_rec_byte  (void) 
{
while (!(UCSRA & (1<<RXC))) ;
return UDR ; 

}
void uart_send_string (const unsigned char *str)  
{
unsigned char i = 0 ; 

while (str [i] != '\0')
{
uart_send_byte (str[i]) ; 
i++ ; 

}
}

void uart_rec_string (unsigned char *str) 
{
unsigned char i = 0 ;
str[i] = uart_rec_byte() ;
while (str [i] != '#') 
{
i++ ;
str [i] = uart_rec_byte ();

}
str[i] = '\0' ; 
}
/***********************************************************************************************/ 
/*
If you will use interrupt instead of polling you should 
have two volatie variables : 
volatile unsigned char recieved_data = 0 ; 
volatile unsigned char transmit_data = 0 ;

*/
// This is interrupt service routine for sending one character 
// ----------------------------------------------------------------
ISR (USART_UDRE_vect)
{
	UDR = transmit_data;	 
	PORTB ^= 1<<PB0 ; 		// Led indicator change its state when send 
}
// This is interrupt service routine for recieving one character 
// ----------------------------------------------------------------
ISR (USART_RXC_vect)
{
recieved_data = UDR ; 	
PORTB ^= 1<<PB1 ;			// Led indicator change its state when Recieve  
}



















