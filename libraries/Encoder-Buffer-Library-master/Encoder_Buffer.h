#ifndef ENCODER_BUFFER_H
#define ENCODER_BUFFER_H


#include <Arduino.h>
#include <SPI.h>

class Encoder_Buffer{
      
      public:
              Encoder_Buffer(int _slaveSelectEnc);
              ~Encoder_Buffer();
      
              void initEncoder(); 
              long readEncoder(); 
              void clearEncoderCount(); 
              void debugEncoder();  
          
              unsigned char encodercount[5] = {0x00, 0x00, 0x00, 0x00};
              
      private:
              int slaveSelectEnc;
              long EncoderActualValue(int usedPin);
              void _clearEncoderCount(int usedPin);
      
      
};

#endif
