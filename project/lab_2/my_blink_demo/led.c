#include <msp430.h>
#include "led.h"
#include "my_switches.h"
#include "my_buzzer.h"

//unsigned char red_on = 0, green_on = 0;/
//unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};


void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update()
{
  /*if (led_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
    led_changed = 0;
  }
  */
  if(switch_state_down){
    char ledFlags = 0;
    ledFlags |= switch_state_down ? LED_GREEN :0;
    ledFlags |= switch_state_down ? 0:LED_RED;
    P1OUT &= (0xff-LEDS) | ledFlags;
    P1OUT |= ledFlags;
  
  }
  else if(sw_state_down_1){
    char ledFlags = 0;
    ledFlags |= sw_state_down_1 ? LED_RED : 0;
    ledFlags |= sw_state_down_1 ? 0: LED_GREEN;
    P1OUT &= (0xff-LEDS) | ledFlags;
    P1OUT |= ledFlags;

  }
  else if (sw_state_down_2){
    buzzer_set_period(1000);
  }
  else if(sw_state_down_3){
    char ledFlags = 0;
    ledFlags |= sw_state_down_3 ? 0:0;

    P1OUT &= (0xff -LEDS) | ledFlags;
    P1OUT |= ledFlags;
    
  }
  else if(led_changed){
    char ledFlags = redVal[red_on] | greenVal[green_on];
    P1OUT &=(0xff ^ LEDS) | ledFlags;
    P1OUT |= ledFlags;
  }
  switch_state_changed = 0;
}

