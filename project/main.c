#include <msp430.h>
#include <libTimer.h>
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "aFunctions.h"

#define LED_GREEN BIT6

u_char width = screenWidth, height = screenHeight;
int deltaCpattern[8] = {1,-1,0,0,-1,1,0,0}, deltaRpattern[8] = {0,0,-1,1,0,0,1,-1}, deltaC = 1, deltaR = 0;
u_int bgColor = 0x3666;
u_char originC = screenWidth/2 - 20, originR = screenHeight/2 - 6;
short redrawScreen = 0, animationState = 0;

void wdt_c_handler()
{
  static int secCount = 0, length = 0, i = 0;
  
  if (switch4_state_down){
    secCount++;

    if (secCount == 15){
      secCount = 0;
      length++;

      if(length == 20){
	length = 0;
    
	if(i<7){
	  i++;
	}else{
	  i = 0;
	}
    
	deltaC = deltaCpattern[i];
	deltaR = deltaRpattern[i];
      }

      redrawScreen = 1;
    }
  }
}

int main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  switch_init();

  enableWDTInterrupts();

  clearScreen(COLOR_WHITE);
  
  or_sr(0x8);

  while(1){
    
    if(switch1_state_down){
      bgColor = changeScreen(bgColor);
      animationState = 0;
      
      fillRectangle(40,40, 50, 70, COLOR_RED);

    }else if(switch2_state_down){
      clearScreen(COLOR_GOLD);
      animationState = 0;

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
      clearScreen(COLOR_RED);
      animationState = 0;
      
      drawString11x16(10,10, "WOW", COLOR_WHITE, COLOR_RED);
      drawString11x16(10,30, "NEW", COLOR_WHITE, COLOR_RED);
      drawString11x16(10,50, "FONT", COLOR_WHITE, COLOR_RED);
      drawString11x16(10,70, "YEAH!", COLOR_WHITE, COLOR_RED);

    }else if(switch4_state_down){
      if (!animationState) clearScreen(COLOR_CYAN);
      animationState = 1;

      drawString11x16(originC, originR, "*wow*", COLOR_YELLOW, COLOR_CYAN);
      originC+=deltaC;
      originR+=deltaR;
    }

    P1OUT &= ~LED_GREEN;
    redrawScreen = 0;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
