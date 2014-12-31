/*
 * Demonstration on how to redirect stdio to UART. 
 *
 * http://appelsiini.net/2011/simple-usart-with-avr-libc
 *
 * To compile and upload run: make clean; make; make program;
 * Connect to serial with: screen /dev/tty.usbserial-*
 *
 * Copyright 2011 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 */
 
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#include "main.h"
#include "uart.h"

void rawmouse() {
      putc(0xFD,stdout);
      putc(0x00,stdout);
      putc(0x03,stdout);
      putc(0x00,stdout);
      putc(0x03,stdout);
      putc(0x00,stdout);
      putc(0x00,stdout);
      putc(0x00,stdout);
      putc(0x00,stdout);
}

int main(void) {    

    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    

    DDRB = 0xFF;
    int io;
    DDRD = 0x00;
    DDRC = 0x00;
    PORTC = 0xFF;
    int i=0;
    while(1) {
      for(i=1; i<2; i>>1) {
	PORTB = 0;
	/* io = PINC; */
	putc('a',stdout);
	if( (PINC & 16)==0) putc('b',stdout);
	if( (PINC & 8) ==0) putc('c',stdout);

	_delay_ms(100);
      }

    }
        
    return 0;
}
