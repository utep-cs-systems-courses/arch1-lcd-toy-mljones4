#include <msp430.h>
#include <libTimer.h>
#include "stateMachines.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6

u_char width = screenWidth, height = screenHeight, radius = 20;
short redrawScreen = 1;

void wdt_c_handler()
{
  static int secCount = 0;

  if (switch_state_changed){
    // redrawScreen = 1;
    switch_state_changed = 0;
  }
}

void state_advance()
{
  P1OUT |= LED_GREEN;

  //redrawScreen = 0;
  
  if(switch1_state_down){
    clearScreen(COLOR_CYAN);
    fillRectangle(40,40, 50, 70, COLOR_RED);
   
  }else if(switch2_state_down){
    clearScreen(COLOR_GOLD);
    
    char length = 30, startC = width/2-length/2, startR = height/2 - length;
    int cPattern[8] = {1,1,0,-1,-1,-1,0,1}, rPattern[8] = {0,1,1,1,0,-1,-1,-1};
    char limit = length;
    
    for(int j = 0; j<8; j++){
      if((cPattern[j] == -1 || cPattern[j] == 1) && (rPattern[j] == 1 || rPattern[j] == -1)){
	limit = length/2;
      }else{
	limit = length;
      }
      
      for(int i = 0; i < limit; i++){
	drawPixel(startC+=cPattern[j], startR+=rPattern[j], COLOR_PURPLE);
      }
    }
    
  }else if(switch3_state_down){
    drawString8x12(20,20, "NEW FONT WOWOWOW", COLOR_RED, COLOR_BLUE);
  }

  P1OUT &= ~LED_GREEN;
  or_sr(0x10);
}
