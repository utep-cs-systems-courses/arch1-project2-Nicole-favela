#include <msp430.h>
#include "led.h"
#include "my_switches.h"
#include "my_buzzer.h"
#include "stateMachines.h"
//unsigned char red_on = 0, green_on = 0;/
//unsigned char led_changed = 0;
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
    char ledFlags = redVal[red_on] | greenVal[green_on];
    
    P1OUT &= (0xff-LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
  }
    if(switch_state_changed){
      char ledFlags = 0;
      switch(select_button(button)){
      case 1:
	ledFlags |= LED_RED;
	break;
      case 2:
	ledFlags |= LED_GREEN;
	break;
      case 3:
	ledFlags = 0;
	break;
      case 4:
	ledFlags = 0;
	break;
    }
	P1OUT &= (0xff-LEDS) | ledFlags;
	P1OUT |= ledFlags;
    }
      /* if(switch_state_down){
    char ledFlags = 0;
    ledFlags |= switch_state_down ? LED_GREEN :0;
    ledFlags |= switch_state_down ? 0:LED_RED;
    P1OUT &= (0xff-LEDS) | ledFlags;
    P1OUT |= ledFlags;
  
  }
  if(sw_state_down_1){
    char ledFlags = 0;
    ledFlags |= sw_state_down_1 ? LED_RED : 0;
    ledFlags |= sw_state_down_1 ? 0: LED_GREEN;
    P1OUT &= (0xff-LEDS) | ledFlags;
    P1OUT |= ledFlags;

  }
  if (sw_state_down_2){//button 3
    char ledFlags = 0;
    // ledFlags |= sw_state_down_2;
    // ledFlags |= sw_state_down_2 ? LED_GREEN: LED_RED;
    P1OUT &= (0xff ^LEDS) | ledFlags;
    P1OUT |=ledFlags;
    
  }
  if(sw_state_down_3){
    char ledFlags = 0;
    /* ledFlags |= sw_state_down_3 ? 0:0;

    P1OUT &= (0xff -LEDS) | ledFlags;
    P1OUT |= ledFlags;
      *//*
    turn_led_off();
  }
  if(led_changed){
     char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &=(0xff - LEDS) | ledFlags;
    P1OUT |= ledFlags;
   
    // turn_led_on();
  }
  
  switch_state_changed = 0;
	*/
}

