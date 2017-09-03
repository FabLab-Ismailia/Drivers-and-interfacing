/*
 * micro_config.h
 *
 *  Author: Mohamed Hemed
 */ 


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif  

/*CHOOSE BETWEEN SLEEP MODES */
//---------------------------------------
#define Idle_MODE  					0x00
#define ADC_Noise_Reduction  		0x10
#define Power_down					0x20
#define Power_save 					0x30
#define Standby						0x60
#define Extended_Standby 			0x70
#define SLEEP_CPU				    (asm ("sleep")) 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
