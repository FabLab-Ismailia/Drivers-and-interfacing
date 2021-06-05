/* blink led with tiva c Arm cortex m4 processor */
/* ********************************************* */ 
#include "tm4c123gh6pm.h"

/*
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
*/
int main()
{
  SYSCTL_RCGCGPIO_R = 0x20 ;  // set clk to portf 
  GPIO_PORTF_DIR_R =  0x0e ; 
  GPIO_PORTF_DEN_R =  0x0e ;  
  void software_delay_ms(int delay_ms) ;   
  while(1) 
  {
  GPIO_PORTF_DATA_R = 0x0E; 
  software_delay_ms(500) ; 
  GPIO_PORTF_DATA_R = 0x00; 
  software_delay_ms(500) ; 
  
  }
  
  
  return 0;
}

/*
software delay calculation : 
-------------------------------
clk = 16 MHZ       cpu tick = 1 / clk        1ms / processor tick = 16000 
while loop take about 6 cycles or ticks 
so 16000 / 6 = 3180  
so every 1ms cpu tick about 3180 
*/

void software_delay_ms(int delay_ms) 
{
long int delay_time = 3180 *  delay_ms ; 
while (-- delay_time) ; 
} 
