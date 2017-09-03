/*

This is header file of lcd library
by : mohammed sayed hemed 

*/



#ifndef LCD_H_ 
#define LCD_H_ 

#include "micro_config.h"

#define data_port_dir    DDRC
#define control_port_dir DDRD 
#define data_port 		 PORTC 
#define control_port 	 PORTD
#define RS 					4		
#define En 					6
#define RW 					5
#define mode4		4
#define mode8		8
static char mode ; 
void lcd_init_mode4(void) ;
void lcd_init_mode8(void) ; 
void lcd_send_cmd_mode4 (unsigned char cmd) ;
void lcd_send_cmd_mode8 (unsigned char cmd) ;

void lcd_send_data_mode4 (unsigned char data) ;
void lcd_send_data_mode8 (unsigned char data)  ;
 
 
void lcd_send_string_mode4 (char * str) ;
void lcd_send_string_mode8 (char * str) ;

void lcd_gotoxy_mode4 (unsigned char x , unsigned char y) ;
void lcd_gotoxy_mode8 (unsigned char x , unsigned char y) ;

void LCD_intgerToString_mode4(long int data);
void LCD_intgerToString_mode8(long int data);



#endif
