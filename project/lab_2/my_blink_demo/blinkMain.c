//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "timerLib/libTimer.h"
#include "led.h"
#include "my_buzzer.h"
#include "my_switches.h"


int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  switch_init();
  buzzer_init();
  
  enableWDTInterrupts();	/* enable periodic interrupt */

  or_sr(0x18);		/* CPU off, GIE on */
}
