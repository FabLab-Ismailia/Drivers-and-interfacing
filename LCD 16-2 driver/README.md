# LCD-16-2-driver-
***Library to use lcd 16*2 with avr microcontroller and you can use it with any other type of microcontroller like 
PIC - ARM - 8051 But you'll need to change the names of control port - data port for 
each type .***

***This is lcd source file library 
You can choose between 4-bit mode or 8-bit mode :***
------------------------------------------------
***according to your use and requirements*** :

It is a trade off!
You save up to 4 I/O lines using 4-bit mode over that of 8-bit mode
but the data transfer takes twice as long in 4-bit mode as it does in 8-bit mode.
If I/O is limited, 4-bit mode might be the way to go.
If I/O is plentiful, but time is important 8-bit mode may be the way to go.

if you use 4-bit mode you need 4pins to send data + 2 pins to control it 
the third control pin almost connect to Gnd as it allow you to write to lcd 
seldom when you need to read from lcd so you can comment all the lines in the whole library : 
------------------------------------------------------------------------------------------------
// control_port_dir |= (1<<RS) ;
// control_port     &=(~1<<RW);
------------------------------------------------------------------------------------------------
to save one additonal pin . 

But if want read from lcd you let the all these lines uncomment in the whole library  : 
----------------------------------
// control_port_dir |= (1<<RS) ;
// control_port     &=(~1<<RW);
----------------------------------
By : mohammed sayed hemed 
   : Embedded system geek :D 

