/*
This is lcd source file library 
you can choose between 4-bit mode or 8-bit mode 
according to your use and requirements   

It is a trade off!
You save up to 4 I/O lines using 4-bit mode over that of 8-bit mode
but the data transfer takes twice as long in 4-bit mode as it does in 8-bit mode.
If I/O is limited, 4-bit mode might be the way to go.
If I/O is plentiful, but time is important 8-bit mode may be the way to go.

if you use 4-bit mode you need 4pins to send data + 2 pins to control it 
the third control pin almost connect to Gnd as it allow you to write to lcd 
seldom when you need to read from lcd so you can comment all the lines in the whole library : 
**********************************
// control_port_dir |= (1<<RS) ;
// control_port     &=(~1<<RW);
**********************************
to save one additonal pin . 

But if want read from lcd you let the all these lines uncomment in the whole library  : 
**********************************
// control_port_dir |= (1<<RS) ;
// control_port     &=(~1<<RW);
**********************************
By : mohammed sayed hemed 

*/


#include "lcd.h"

void lcd_init_mode4(void)
{
//*********************************************	
// AFTER POWER UP YOU SHOULD WAIT 15ms BEFORE 
// SENDING INITIALIZING COMMANDS TO LCD .
// BUT IF LCD_INIT FUNCTION ISN'T YOUR FIRST 
// COMMENT THIS LINE    //_delay_ms (15) ; 	
//********************************************* 
_delay_ms (15) ; 						
//************************************************

data_port_dir |= 0xF0;
control_port_dir |= (1<<RS) ;
control_port_dir |=(1<<RW)|(1<<En)  ; 
 						
control_port &=(~1<<En);
	
//INIT COMMANDS TO TELL LCD TO GO ON 4-BIT MODE : 
//*********************************************** 
lcd_send_cmd_mode4 (0x33) ; 					
lcd_send_cmd_mode4 (0x32) ; 
lcd_send_cmd_mode4 (0x28)	; 					// 2 lines , 5*7 matrix , 4-bit mode 

// TO INIT YOU SOME COMMANDS SHOULD BE RUN : 
//********************************************	
lcd_send_cmd_mode4 (0x0e) ; 					// command to display on - cursor blinking
lcd_send_cmd_mode4 (0x01) ; 					// command to clear display to lcd 	
_delay_us (2000) ; 						// waiting time to clear lcd display 
lcd_send_cmd_mode4 (0x06);					// shift cursor to right . 

} 

void lcd_init_mode8(void) 
{
_delay_ms (15) ; 	
data_port_dir |= 0xFF; 
control_port_dir |= (1<<RS) ;
control_port_dir |=(1<<RW)|(1<<En)  ;	
control_port &=(~1<<En);	
	
lcd_send_cmd (0x28) ;					// 2 lines , 5*7 matrix , 8-bit mode 
// TO INIT YOU SOME COMMANDS SHOULD BE RUN : 
//********************************************	
lcd_send_cmd_mode8 (0x0e) ; 					// command to display on - cursor blinking
lcd_send_cmd_mode8 (0x01) ; 					// command to clear display to lcd 	
_delay_us (2000) ; 						// waiting time to clear lcd display 
lcd_send_cmd_mode8 (0x06);					// shift cursor to right . 	
}


void lcd_send_data_mode4 (unsigned char data)
{
	control_port &=(~(1<<RW));				//  RW = 0 >> for write to lcd 
	control_port |=(1<<RS);					// 	Rs = 1 >> send data to lcd register    
	data_port = data &0xf0 ; 			//  send high nible to D4 : D7
	control_port |= (1<<En);			// HIGH	
	_delay_us (1);						// TO
	control_port &=(~(1<<En)) ;			// LOW PULSE 
	data_port = data << 4 ; 			//  send low nibble to D4 : D7
 	control_port |= (1<<En);			// HIGH	
	_delay_us (1);						// TO
	control_port &=(~(1<<En)) ;			// LOW PULSE 
	
	_delay_us (100) ; 					// Wait 100 us to let lcd to run command 
	
	
    }

void lcd_send_data_mode8 (unsigned char data)
{   
		
	control_port &=(~(1<<RW));				//  RW = 0 >> for write to lcd 
	control_port |=(1<<RS);					// 	Rs = 1 >> send data to lcd register 	
	data_port = data ; 
	//High to low pulse to enable lcd 
	//********************************** 
	control_port |= (1<<En);			// HIGH	
	_delay_us (1);						// TO
	control_port &=(~(1<<En)) ;			// LOW PULSE
	_delay_us (100);					// Wait 100 us to let lcd to write data on screen 
	
}




void lcd_send_cmd_mode4 (unsigned char cmd)
{
		 
	control_port &=(~(1<<RW));		// RW = 0 , almost RW = 0 , as you alaways write from lcd 
										// but you can connect it to Gnd - then control pins = 2 pins only 
	control_port &=(~(1<<RS));		// Rs = 0 >> to command
	data_port = cmd &0xf0 ;  			//  send high nible to D4:D7 and ignore low niblle   
    
	control_port |= (1<<En);			// HIGH	
	_delay_us (1);						// TO
	control_port &=(~(1<<En)) ;			// LOW
	_delay_us (100);					// PULSE
    
	data_port = cmd<<4 ; 				// shift the low 4-bits of cmd to the left to send the low nible to D4:D7 
	
	control_port |= (1<<En);			// HIGH	
	_delay_us (1);						// TO
	control_port &=(~(1<<En)) ;			// LOW
	_delay_us (100);					// PULSE
} 
	
   
void lcd_send_cmd_mode8 (unsigned char cmd)
 
	{
	  control_port &=(~(1<<RW));		// RW = 0 , almost RW = 0 , as you alaways write from lcd 
										// but you can connect it to Gnd - then control pins = 2 pins only 
	  control_port &=(~(1<<RS));		// Rs = 0 >> to command
	data_port = cmd ; 
	control_port |= (1<<En);
	_delay_us (1);
	control_port &=(~(1<<En)) ;
	_delay_us (100);
	
	}
	


void lcd_send_string_mode4 (char * str)
{
unsigned char a =0  ; 
while (str[a]!= 0 )
{
lcd_send_data_mode4 (str [a]) ; 
a++ ; 
}
}
 
void lcd_send_string_mode8 (char * str)
{
unsigned char a =0  ; 
while (str[a]!= 0 )
{
lcd_send_data_mode8 (str [a]) ; 
a++ ; 
}
}
 
 
 
 
void lcd_gotoxy_mode4 (unsigned char x , unsigned char y) 
{
unsigned char first_char_add[] = {0x80 ,0xC0 ,0x94 , 0xD4} ; 
lcd_send_cmd_mode4 (first_char_add[y-1]+ x-1) ; 
_delay_us (100);

}

void lcd_gotoxy_mode8 (unsigned char x , unsigned char y) 
{
unsigned char first_char_add[] = {0x80 ,0xC0 ,0x94 , 0xD4} ; 
lcd_send_cmd_mode8 (first_char_add[y-1]+ x-1) ; 
_delay_us (100);

}




void LCD_intgerToString_mode4(long int data)
{
	char buff[32]; 				/* String to hold the ascii result */
	ltoa(data,buff,10); 			/* 10 for decimal */
	lcd_send_string_mode4(buff);
}

void LCD_intgerToString_mode8(long int data)
{
	char buff[32]; 				/* String to hold the ascii result */
	ltoa(data,buff,10); 			/* 10 for decimal */
	lcd_send_string_mode8(buff);
}








