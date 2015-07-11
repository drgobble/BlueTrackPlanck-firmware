/*
 * My bluetooth planck firmware. Super slim.
 *
 */
 
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

#include "main.h"
#include "uart.h"
#include "keys.h"



#include "tmkps2/ps2_mouse.h"
#include "tmkps2/report.h"

/* char matrix[4][12] = { */
/*   {KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T, KEY_P,   KEY_2, KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P}, */
/*   {KEY_A,KEY_S,KEY_D,KEY_F,KEY_G, KEY_2,   KEY_2, KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON}, */
/*   {KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B, KEY_3,   KEY_2, KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_BACKSLASH}, */
/*   {KEY_6,KEY_7,KEY_8,KEY_9,KEY_0, KEY_NONE,KEY_2, KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P}, */
/* }; */

#define N_LAYER 2
#define MODE_K 0
#define MODE_M 1
#define MODE_L 2
#define K MODE_K
#define M MODE_M
#define L MODE_L


char state[4*12];

char mode[N_LAYER*4*12] = {
  K,K,K,K,K, K,K, K,K,K,K,K,
  K,K,K,K,K, M,K, K,K,K,K,K,
  K,K,K,K,K, K,K, K,K,K,K,K,
  K,K,M,M,M, K,K, L,K,K,K,K,

  K,K,K,K,K, K,K, K,K,K,K,K,
  K,K,K,K,K, M,K, K,K,K,K,K,
  K,K,K,K,K, K,L, L,L,L,L,L,
  K,K,M,M,M, K,K, L,K,K,K,K
};

#undef K
#undef M
#undef L

#define L_ONE 1
#define MOUSE_L 2
#define MOUSE_R 3
#define MOUSE_D 4
#define MOUSE_U 5
#define CLICK_L 6
#define CLICK_R 7

char matrix[N_LAYER*4*12] = {
  K_Q,     K_W,    K_E,     K_R,    K_T,      K_BRACKET_L,K_BRACKET_R,K_Y,  K_U,      K_I,    K_O,        K_P,
  K_A,     K_S,    K_D,     K_F,    K_G,      M_CONTROL_L,K_RETURN,   K_H,  K_J,      K_K,    K_L,        K_SEMICOLON,
  K_Z,     K_X,    K_C,     K_V,    K_B,      K_BACKSLASH,K_BACKSPACE,K_N,  K_M,      K_COMMA,K_PERIOD,   K_SLASH,
  K_ESCAPE,K_TAB,  M_ALT_L, M_GUI_L,M_SHIFT_L,K_NONE,     K_SPACE,    L_ONE,K_ARROW_L,K_ARROW_D,K_ARROW_U,K_ARROW_R,

  K_F1,    K_F2,   K_F3,    K_F4,   K_F5,     K_F6,       K_F7,       K_F8,  K_F9,     K_F10,    K_F11,    K_F12,
  K_1,     K_2,    K_3,     K_4,    K_5,      M_CONTROL_L,K_RETURN,   K_6,   K_7,      K_8,      K_9,      K_0,
  K_APOSTROPHE,K_MINUS,K_EQUAL,K_NONE, K_NONE,      K_GRAVE,    CLICK_R,    CLICK_L,MOUSE_L,  MOUSE_D,  MOUSE_U,  MOUSE_R,
  K_ESCAPE,K_NONE, M_ALT_L, M_GUI_L,M_SHIFT_L,K_NONE,     K_SPACE,    L_ONE, K_HOME,   K_PAGE_D, K_PAGE_U, K_END
};

int mouse_x = 0;
int mouse_y = 0;
int mouse_click = 0;

int mouse_x_last = 0;
int mouse_y_last = 0;
int mouse_click_last = 0;


void reset_mouse_report() {
  mouse_x_last = mouse_x;
  mouse_y_last = mouse_y;
  mouse_click_last = mouse_click;

  mouse_x = 0;
  mouse_y = 0;
  mouse_click = 0;
}

void send_raw_mouse_report() {

  int newmouse = 0;
  if (mouse_click != mouse_click_last) newmouse = 1;
  if (mouse_x != mouse_x_last) newmouse = 1;
  if (mouse_y != mouse_y_last) newmouse = 1;
  if (newmouse == 0) return;

  uart_putchar(0xFD,stdout);
  uart_putchar(0x00,stdout);
  uart_putchar(0x03,stdout);
  uart_putchar(mouse_click,stdout);
  uart_putchar(mouse_x,stdout);
  uart_putchar(mouse_y,stdout);
  uart_putchar(0x00,stdout);
  uart_putchar(0x00,stdout);
  uart_putchar(0x00,stdout);
}

int active_layer = 0;
int nkey=0;
char keys[6];
char modifier;

int nkey_last;
char keys_last[6];
char modifier_last;

void reset_report() {
  nkey_last = nkey;
  for(int i=0;i<6;i++) keys_last[i] = keys[i];
  modifier_last = modifier;

  nkey=0;
  for(int i=0;i<6;i++) keys[i]=0x00;
  modifier = 0;
}


void send_raw_key_report() {
  bool newkey = 0;
  if( modifier != modifier_last) newkey = 1;
  for(int i=0;i<6;i++) if(keys_last[i]!=keys[i]) newkey = 1;

  if (newkey == 0) return;

  uart_putchar(0xFD,stdout);
  uart_putchar(modifier,stdout); // Modifier
  uart_putchar(0x00,stdout);
  for(int i=0;i<6;i++) {
    uart_putchar(keys[i],stdout);
  }
}

void push_key(char code) {
  keys[nkey]=code;
  nkey++;
}
void push_modifier(char mod) {
  modifier |= mod;
}
void special(char data, int st) {
  switch(data) {
  case L_ONE:
    active_layer = (st?1:0);
    break;
  case MOUSE_U:
    if(st) mouse_y = -10;
    break;
  case MOUSE_D:
    if(st) mouse_y =  10;
    break;
  case MOUSE_L:
    if(st) mouse_x = -10;
    break;
  case MOUSE_R:
    if(st) mouse_x =  10;
    break;
  case CLICK_L:
    if(st) mouse_click |= 1;
    break;
  case CLICK_R:
    if(st) mouse_click |=  2;
    break;
  }
}

void process_key(int id, int st) {
  switch(mode[active_layer*4*12+id]) {
  case MODE_K:
    if(st && state[id]) push_key(matrix[active_layer*4*12+id]);
    break;
  case MODE_M:
    if(st && state[id]) push_modifier(matrix[active_layer*4*12+id]);
    break;
  case MODE_L:
    if( (st && state[id]) || ( (!st) && (!state[id]) ) ) special(matrix[active_layer*4*12+id],st);
    break;
  default:
    break;
  }
  state[id] = st;
}

extern report_mouse_t mouse_report;

int main(void) {
  DDRB = 0b00011110; //Configure some of them to be input, some to output
  PORTB = 0xFF; // all of them to pull up or high

  DDRC = 0x00; // All of them to input
  PORTC = 0xFF; // with a pull up
  PORTD = 0xFF;
  
  _delay_ms(100);

  uart_init();
  stdout = &uart_output;
  stdin  = &uart_input;
  ps2_mouse_init();
  /* ps2_init(); */
  _delay_ms(100);
  reset_report();
  send_raw_key_report();

  DDRD &= 0b00011111; // D will be reconfigured by the uart module.

  int i,j;
  while(1) {
    reset_report();
    reset_mouse_report();
    /* keys[0] = K_A; */
    for(j=0; j<4; j++) {
      PORTB = ~(1<<(1+j));
      for(i=0; i<6; i++) {
    	  process_key(j*12+i, !(PINC & (1<<i)));
      }
      process_key(j*12+i, !(PINB & 1)  );
      i++;
      process_key(j*12+i, !(PIND & (1<<7)));
      i++;
      process_key(j*12+i, !(PIND & (1<<6)));
      i++;
      process_key(j*12+i, !(PIND & (1<<5)));
      i++;
      process_key(j*12+i, !(PINB & (1<<7)));
      i++;
      process_key(j*12+i, !(PINB & (1<<6)));
    }
    send_raw_key_report();

    ps2_mouse_task();

    mouse_report.x >>= 1;
    mouse_report.y >>= 1;

    mouse_x = mouse_report.x;
    mouse_y = mouse_report.y;
    send_raw_mouse_report();

  }
        
  return 0;
}

