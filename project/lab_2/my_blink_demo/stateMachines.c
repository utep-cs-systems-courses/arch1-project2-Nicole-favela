#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "my_buzzer.h"
#include "my_switches.h"
//static enum {off = 0,on = 1,} buzzer_tone;
char unsigned red_on =0,green_on = 0, led_changed = 0;
int tones[] = {1000,0,200,0,1800,0,1500,0,3000,0,4000,100,0,2500,0,20};
//my code
char button_states()
  
{
  static char st = 0;
  switch(st){
  case 0:
    red_on = 1;
    buzzer_set_period(200);
    st = 1;
    break;
  case 1:
    red_on = 0;
    buzzer_set_period(1500);
    st = 2;
    break;
   

  }
}
char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
  int i = 0;
  int count = 0;
  switch(select_button(count))
  {
    case 1:
      buzzer_set_period(tones[i++]);
      //buzzer_set_period(0);
      break;
    case 2:
      turn_buzzer_off();
      break;
    case 3:
      led_update();
      break;

    case 4:
      buzzer_set_period(4000);
      break;
  }
}
int select_button(button)
{
  if(switch_state_down)
  {
    button = 1;
  }
  else if(sw_state_down_1)
  {
    button = 2;
  }
  else if(sw_state_down_2)
  {
    button =3;
  }
  else if(sw_state_down_3)
  {
    button = 4;
  }
  return button;
}


