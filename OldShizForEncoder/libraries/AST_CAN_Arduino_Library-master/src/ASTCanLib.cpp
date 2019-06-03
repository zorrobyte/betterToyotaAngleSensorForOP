/**********************************************************************************
 * Created by Atlantis Specialist Technologies
 * by James Blakey-Milner, 1 Aug 2017.
 * Ported the library to the Arduino platform
 * Main header file to include the library
 * Note! this file is in early development
 * (alpha) and is likely to change without notice.
 **********************************************************************************/
 
#include "ASTCanLib.h"

void canInit(long baud){
  // Clock prescaler
  CLKPR  = ( 1 << CLKPCE );          // Set Clock Prescaler change enable
  CLKPR  = 0x00;
  // Setup ports
  DDRB  |= (1<<DDB1)|(1<<DDB4);
  DDRD  |= (1<<DDD5);                // TxCan
  PORTB |= (1<<PORTB1)|(1<<PORTB4); // set LED & CAN_STBY high
  PORTD |= (1<<PORTD5);             // txCAn High
  // Flash LED off
  _delay_ms(50);
  PORTB &= ~(1<<PORTB1);            // RST Led
  PORTB &= ~(1<<PORTB4);            // Go into normal mode (CAN_STBY low)
  _delay_ms(50);
  can_init(0,baud);
}

void clearBuffer(uint8_t *Buffer){
  for (int i=0; i<8; i++){
    Buffer[i] = 0x00;
  }
}