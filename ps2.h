#ifndef H_PS2
#define H_PS2

#define MCLK 2
#define MDATA 3

void gohi(int pin);
void golo(int pin);

void toggle_clk(void); 
void mouse_write(char data);

void ps2_init(void);
void mouse_stat(int * mstat, int * mx, int * my);
#endif
