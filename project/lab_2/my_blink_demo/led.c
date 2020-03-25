#include <msp430.h>
#include "led.h"
#include "my_switches.h"
#include "my_buzzer.h"
#include "stateMachines.h"

//static enum {led_off = 0, dim = 1, led_on =2}led_states;
char button = 0;
static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};
void turn_led_off()
{
  char ledFlags = 0;
  P1OUT &= (0xff-LEDS) | ledFlags;
  P1OUT |= ledFlags;
}
void turn_led_on()
{
  char ledFlags = 0;
  ledFlags |= LED_GREEN;
  ledFlags |= LED_RED;
  P1OUT &= (0xff -LEDS) | ledFlags;
  P1OUT |=ledFlags;
}

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(button)
{
  if (led_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];//flashes ledso
    
    P1OUT &= (0xff-LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
  }
    if(switch_state_changed){
      char ledFlags = 0;
      switch(select_button(button)){ //does something different for every button pushed
      case 1:
	//ledFlags |= LED_RED;
	ledFlags |= redVal[red_on];//flashes red
	P1OUT &= (0xff^LEDS) | ledFlags; 
	P1OUT |= ledFlags;//outputs leds 
	break;
      case 2:
	//turns green on 
	ledFlags |= LED_GREEN;
	ledFlags |= LED_RED;//keeps red on
	//ledFlags |= LEDS;
	P1OUT &= (0xff^LEDS) | ledFlags;
	P1OUT |= ledFlags;
	break;
      case 3:
	ledFlags = 0;//dims leds
	P1OUT &= (0xff^LEDS) | ledFlags;
	P1OUT |= ledFlags;
	break;
      case 4:
	ledFlags = 0;//dims leds
	P1OUT &= (0xff ^LEDS) | ledFlags;
	P1OUT |= ledFlags;
	break;
    }
    
    }
}
    
