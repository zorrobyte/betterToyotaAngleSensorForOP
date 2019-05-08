#include "Encoder_Buffer.h"

//-- public methods --//

//<<constructor>>
Encoder_Buffer::Encoder_Buffer(int _slaveSelectEnc){
  
 slaveSelectEnc = _slaveSelectEnc;

 
  pinMode(slaveSelectEnc, OUTPUT);
  SPI.begin();
   
}

Encoder_Buffer::~Encoder_Buffer(){};
// ****************************************************
// Initializes our encoders
// RETURNS: long
// ****************************************************
void Encoder_Buffer::initEncoder() {
  // Raise select pins
  // Communication begins when you drop the individual select signsl
  digitalWrite(slaveSelectEnc, HIGH);

  // Initialize encoder
  //    Clock division factor: 0
  //    Negative index input
  //    free-running count mode
  //    x4 quatrature count mode (four counts per quadrature cycle)
  // NOTE: For more information on commands, see datasheet
  digitalWrite(slaveSelectEnc, LOW);       // Begin SPI conversation
  SPI.transfer(0x88);                       // Write to MDR0
  SPI.transfer(0x03);                       // Configure to 4 byte mode
  digitalWrite(slaveSelectEnc, HIGH);      // Terminate SPI conversation

  clearEncoderCount();
  
}


// ****************************************************
// Reads the Encoders to retreive the updated value.
// RETURNS: long
// ****************************************************
long Encoder_Buffer::readEncoder() {
    
  return EncoderActualValue(slaveSelectEnc);
  
  
}

void Encoder_Buffer::clearEncoderCount() {

   _clearEncoderCount(slaveSelectEnc);
   
}

void Encoder_Buffer::debugEncoder(){
  
   Serial.print( encodercount[0]); Serial.print(" ");
   Serial.print( encodercount[1]); Serial.print(" ");
   Serial.print( encodercount[2]); Serial.print(" ");
   Serial.println( encodercount[3]);
   
}

// ****************************************************
// Resets Encoders to 0x00 0x00 0x00 0x00 (0 0 0 0)
// RETURNS: N/A
// ****************************************************
void Encoder_Buffer::_clearEncoderCount(int usedPin){
  
   // Set encoder1's data register to 0
  digitalWrite(usedPin, LOW);     // Begin SPI conversation
  // Write to DTR
  SPI.transfer(0x98);
  // Load data
  SPI.transfer(0x00);  // Highest order byte
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);  // lowest order byte
  digitalWrite(usedPin, HIGH);    // Terminate SPI conversation

  delayMicroseconds(100);  // provides some breathing room between SPI converrsations

  // Set encoder1's current data register to center
  digitalWrite(usedPin, LOW);     // Begin SPI conversation
  SPI.transfer(0xE0);
  digitalWrite(usedPin, HIGH);    // Terminate SPI conversation
}


long Encoder_Buffer::EncoderActualValue(int usedPin){
   long count_value; 
  // Read encoder
    noInterrupts();           // disable all interrupts
    
    digitalWrite(usedPin, LOW);     // Begin SPI conversation
    SPI.transfer(0x60); // Request count
    encodercount[0]  = SPI.transfer(0x00);   // Read highest order byte
    encodercount[1]  = SPI.transfer(0x00);
    encodercount[2]  = SPI.transfer(0x00);
    encodercount[3]  = SPI.transfer(0x00);  // Read lowest order byte

    digitalWrite(usedPin, HIGH);    // Terminate SPI conversation
    
    count_value = (encodercount[0] << 8) + encodercount[1];
    count_value = (count_value << 8) + encodercount[2];
    count_value = (count_value << 8) + encodercount[3];
    
   // encodercount[0]  = (count_value & 0xFF);
 //   encodercount[1]  = (count_value >>8 & 0xFF);
   // encodercount[2]  = (count_value >>16 & 0xFF);
    //encodercount[3]  = (count_value >>24 & 0xFF);

    interrupts();             // enable all interrupts
  return count_value;
}
