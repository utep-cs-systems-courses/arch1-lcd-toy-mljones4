#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "stateMachines.h"

char switch1_state_down, switch2_state_down, switch3_state_down, switch4_state_down, switch_state_changed, switch_state_down; /* effectively boolean */

short redrawScreen;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  
  switch1_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch2_state_down = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  switch3_state_down = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  switch4_state_down = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */

  switch_state_changed = 1;
  
  switch_state_down = switch1_state_down || switch2_state_down || switch3_state_down;

  if(switch_state_down) redrawScreen = 1;
}
