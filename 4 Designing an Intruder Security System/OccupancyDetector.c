#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2
#include <msp430.h>
// Put some initialization here

//char state = ARMED_STATE;
int main(void){
    char state = ARMED_STATE;
    char count = 0; //Second Counter
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer



     PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                             // to activate previously configured port settings

     P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
     P1DIR |= BIT0;                          // Set P1.0 to output direction
     P6OUT &= ~BIT6;                         //Clear P6.6 output latch for a defined power-on state
     P6DIR |= BIT6;                         //Set P6.6 to output direction
;             // Configure P4.1 to an Input

           P2REN |= BIT5;               // Enable Resistor on P2.3
           P2OUT |= BIT5;
           P4REN |= BIT1;       //Enable Resistor on P4.
           P4OUT |= BIT1;
while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      // Do something in the ARMED state
      // If something happens, you can move into the WARNING_STATE
      // state = WARNING_STATE
        if (!(P2IN & BIT5))
        {  P6OUT ^= BIT6; //Toggle P6.6
           P1OUT &= ~BIT0;   // P1.0 Off

        }
        else
           state = WARNING_STATE;

        __delay_cycles(1500000); //3 Sec delay for on/off
        break;
    }
    case WARNING_STATE:
    {
            if (count == 20 && !(P2IN & BIT5)) {
                state = ALERT_STATE; // If Detected go to ALERT_STATE
                count = 0;
            }
            else if (count == 20 && ((P2IN & BIT5))) {
                state = ARMED_STATE;   //IF Not Detected. go to ARMED_STATE
                count = 0;
            }
          P1OUT ^= BIT0;
          P6OUT &= ~BIT6;
          count++;

          __delay_cycles(500000);  //1 Sec on/off


       break;
    }
    case ALERT_STATE: {
        P1OUT ^= BIT0;
        P6OUT &= ~BIT6;

        if(!(P4IN & BIT1)){
         state = ARMED_STATE;
        }

    }
  }
}
}
