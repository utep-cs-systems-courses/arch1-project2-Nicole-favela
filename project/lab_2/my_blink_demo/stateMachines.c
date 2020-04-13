#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "my_buzzer.h"
#include "my_switches.h"
char unsigned red_on =0,green_on = 0, led_changed = 0;
int tones [] = {1500, 9000,0,3000,1000,7000, 0,6000}; //array that stores different periods for use in changing buzzer states

char i = 0;//used to iterate tones array

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
//state machine for switches
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
  int count = 0;
  switch(select_buttons(count))
  {
    case 1:
      buzzer_set_period(tones[i++]); //cyles through possible tones for button 1 (switch_state_down)
   
      break;
    case 2:
      turn_buzzer_off();//turn sound from first button off
      break;
    case 3:
      led_update();
      break;

    case 4:
      buzzer_set_period(4000);//make one buzzer tone with frequency 2000Hz
      break;
  }
}
//returns int value to determine which switch was presssed
int select_buttons(button)
{
  if(switch_state_down)//first switch
  {
    button = 1;
    if(button == select_button(button))
    {
      button = select_button(button);
    }
  }
  else if(sw_state_down_1)//2nd switch
  {
    button = 2;
    if(button == select_button(button))
    {
      button = select_button(button);
    }
  }
  else if(sw_state_down_2)//3rd switch
  {
    button =3;
    if(button == select_button(button))
    {
       button = select_button(button);
    }
  }
  else if(sw_state_down_3)//4th switch
  {
    button = 4;
    if(button = select_button(button))
    {
      button = select_button(button);
    } 
  }
  return button;//returns button pressed as an int
}


