#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6

int main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  switch_init();

  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_WHITE);

  P1OUT &= ~LED_GREEN;
  or_sr(0x10);
}
