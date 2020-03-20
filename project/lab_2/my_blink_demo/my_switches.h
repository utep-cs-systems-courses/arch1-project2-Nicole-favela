#ifndef switches_included
#define switches_included

#define SW0 BIT0
#define SW1 BIT1
#define SW2 BIT2
#define SW3 BIT3
/* switch1 is p1.3 */
#define SWITCHES (SW0 | SW1 | SW2 | SW3)		/* only 1 switch on this board */

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed , sw_state_down_1, sw_state_down_2,sw_state_down_3; /* effectively boolean */

#endif // included
