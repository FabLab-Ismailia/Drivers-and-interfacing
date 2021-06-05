/*
 tiva c based on cortex-m ARM CPU is a great board which 
 contain 12 timers : 
                    6  use as 16-bit | 32 bit 
                    6  use as 32-bit | 64 bit  they called wide range timers   
 using timers and 
 Edit clk frq by PLL in tiva c 
 mohammed hemed    
*/
#include "tm4c123gh6pm.h"
volatile unsigned long delay ; 
void init_PLL(void)
{  
// use RCC2 to override RCC  
SYSCTL_RCC2_R |=0x80000000 ; 
// bypass Pll during config 
SYSCTL_RCC2_R |=0x00000800 ; 
// select XTAL value in RCC 
// 16 Mhz 10101 >> from data sheet 0x15
SYSCTL_RCC_R = (SYSCTL_RCC2_R & ~0x000007c0) + 0x00000540 ; 
// choose OSC source in RCC2 = main OCS
SYSCTL_RCC2_R &= ~0x00000070 ; 
// activate PLL by clear PWRDN2 
SYSCTL_RCC2_R &= ~0x00002000 ; 
// set divisors you want : 400 Mhz Pll
SYSCTL_RCC2_R |=0x40000000 ;    
SYSCTL_RCC2_R = (SYSCTL_RCC2_R &~0x1fc00000) +(4<<22) ;  
// wait PLL to be stable :
while ((SYSCTL_RIS_R & 0x00000040) == 0) ; 
// Enable PLL by clear Bypass
SYSCTL_RCC2_R &= ~0x00000800 ;
}

void init_timer(void) 
{  
SYSCTL_RCGCTIMER_R |= 0x01 ;
delay = 0; 
TIMER0_CTL_R &= ~0x00000001 ;     // disable timer while config
TIMER0_CFG_R =  0x00000000 ;     // 32 bit mode 
TIMER0_TAMR_R =  0x00000002 ;     // periodic mode 
TIMER0_TAMR_R |= 0x00000010 ;    // up count        
TIMER0_TAILR_R = 0x04c48400 ;    // set load value = 8 Million
TIMER0_CTL_R |=0x00000001 ;     // Enable timer
}
void led_config (void)
{
  SYSCTL_RCGCGPIO_R = 0x20 ;  // set clk to portf 
  delay = SYSCTL_RCC2_R; 
  GPIO_PORTF_DIR_R =  0x0e ; 
  GPIO_PORTF_DEN_R = 0x0e ; 
}

int main (){
delay = 0 ; 
init_PLL() ; 
led_config();
init_timer();
int leds [6] = {0x2 ,0x0, 0x4, 0x0 , 0x8, 0x0} ; 
int index = 0 ;
while (1) 
{
while ((TIMER0_RIS_R & 0x1) == 0 ) ;  // wait until timeout = 0 (plling)
GPIO_PORTF_DATA_R = leds[index++] ;             // toggle led 
if (index == 6 ) index = 0 ; 
TIMER0_ICR_R |= (1<<0) ;              // clear timeout flag 
}
}
