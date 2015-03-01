#include "ps2.h"

#include <util/delay.h>
#include <avr/io.h>

void gohi(int pin) {
  DDRD |= 1<<pin;
  PORTD |= 1<<pin;
  DDRD &= ~(1<<pin);
  PORTD |= 1<<pin;
}
void golo(int pin) {
  DDRD |= 1<<pin;
  PORTD &= ~(1<<pin);
  DDRD &= ~(1<<pin);
  PORTD |= 1<<pin;
}

void toggle_clk(void) {
  gohi(MCLK);
  _delay_us(300);
  golo(MCLK);
  _delay_us(300);
}

void mouse_write(char data) {
  char i;
  char parity = 1;

  gohi(MDATA);
  toggle_clk();
  golo(MDATA);
  _delay_us(300);
  gohi(MCLK);

  /* wait for mouse to take control of clock); */
  while (PIND & 1<<MCLK)
    ;
  /* clock is low, and we are clear to send data */
  for (i=0; i < 8; i++) {
    if (data & 0x01) {
      gohi(MDATA);
    } 
    else {
      golo(MDATA);
    }
    /* wait for clock cycle */
    while (PIND & 1<<MCLK)
      ;
    while (PIND & 1<<MCLK)
      ;
    parity = parity ^ (data & 0x01);
    data = data >> 1;
  } 
  /* parity */
  if (parity) {
    gohi(MDATA);
  } 
  else {
    golo(MDATA);
  }
  /* wait for clock cycle */
    while (PIND & 1<<MCLK)
      ;
    while (PIND & 1<<MCLK)
      ;
  /* stop bit */
  gohi(MDATA);
  _delay_us(50);
  while (PIND & 1<<MCLK)
    ;
  while ( !(PIND & 1<<MCLK) || !(PIND& 1<<MCLK) )
      ;
 golo(MCLK);
}


char mouse_read(void)
{
  char data = 0x00;
  int i;
  char bit = 0x01;

  //  Serial.print("reading byte from mouse\n");
  /* start the clock */
  gohi(MCLK);
  gohi(MDATA);
  _delay_us(50);
  while (PIND & 1<<MCLK)
    ;
  _delay_us(5);  /* not sure why */
  while ( !(PIND & 1<<MCLK)) /* eat start bit */
    ;
  for (i=0; i < 8; i++) {
    while (PIND & 1<<MCLK)
      ;
    if (PIND & 1<<MDATA) {
      data = data | bit;
    }
    while ( !(PIND & 1<<MCLK))
      ;
    bit = bit << 1;
  }
  /* eat parity bit, which we ignore */
  while (PIND & 1<<MCLK)
    ;
  while ( !(PIND & 1<<MCLK))
    ;
  /* eat stop bit */
  while (PIND & 1<<MCLK)
    ;
  while ( !(PIND & 1<<MCLK))
    ;

  /* put a hold on the incoming data. */
  golo(MCLK);
  //  Serial.print("Recvd data ");
  //  Serial.print(data, HEX);
  //  Serial.print(" from mouse\n");
  return data;
}

void ps2_init(void) {
  golo(MCLK);
  gohi(MDATA);

  mouse_write(0xff);
  mouse_read();

  mouse_read();
  mouse_read();

  mouse_write(0xf0);
  mouse_read();

  _delay_ms(100);
}


void mouse_stat(int * mstat, int * mx, int * my) {
  mouse_write(0xeb);
  mouse_read();
  *mstat = mouse_read();
  *mx = mouse_read();
  *my = mouse_read();
}
