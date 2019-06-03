#include <SPI.h>
#include <Encoder_Buffer.h>


#define EncoderCS1 8

long encoder1Reading = 0;

Encoder_Buffer Encoder1(EncoderCS1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  Encoder1.initEncoder();
}

void loop() {
  encoder1Reading = Encoder1.readEncoder();//Read Encoder
  Serial.println(encoder1Reading);
  //Encoder1.clearEncoderCount();// Clear Encoder

}
