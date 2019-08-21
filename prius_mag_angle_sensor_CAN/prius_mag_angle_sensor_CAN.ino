#include <Encoder_Buffer.h>
#include <can.h>
#include <mcp2515.h>
#include <SPI.h>

//CAN
struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(3);

//ANGSENSOR
#define EncoderCS1 10
int32_t encoder1Reading = 0;
int32_t lastencoder1Reading = 0;
int32_t rate = 0;
Encoder_Buffer Encoder1(EncoderCS1);
bool AngleSensorSet = False;
int32_t SteerAngleOffset = 0;

void setup() {
  
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();

  //INIT CAN
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //8Mhz oscillator
  mcp2515.setNormalMode();
  
  //INIT ANGSENSOR
  Encoder1.initEncoder();
}

void loop() {
  //Angle Offset. loop here until we can get an offset
  while(!AngleSensorSet){
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      if(canMsg.can_id == 0x25){
        int16_t SteerAngleRaw = ((canMsg.data[0] & 0xF) << 8) | canMsg.data[1];
        double SteerAngle = SteerAngleRaw * 1.5;
        int8_t SteerFractionRaw = ((canMsg.data[4] >> 4) & 0xF) | (canMsg.data[4] & 0x80); //trick to make my 4 bit int a signed 8 bit int
        double SteerFraction = SteerFractionRaw * 0.1;
        SteerAngle = SteerAngle + SteerFraction;
        Serial.println(SteerAngle);
        SteerAngle = SteerAngle / 0.004901594652; //scale to encoder offset
        SteerAngleOffset = (int32_t)SteerAngle;
        AngleSensorSet = true;
        Serial.print(SteerAngleOffset);
        break;
      }
    }
  }
  //ANGSENSOR
  encoder1Reading = (Encoder1.readEncoder() + SteerAngleOffset); //READ the ANGSENSOR and offset it
  //Serial.println(encoder1Reading);

  rate = abs(encoder1Reading) - abs(lastencoder1Reading);

  lastencoder1Reading = encoder1Reading;

  //CAN
  canMsg1.can_id  = 0x23;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = (encoder1Reading >> 24) & 0xFF; //Bitshift the ANGSENSOR (Cabana errors with 32 bit)
  canMsg1.data[1] = (encoder1Reading >> 16) & 0xFF;
  canMsg1.data[2] = (encoder1Reading >> 8) & 0xFF;
  canMsg1.data[3] = (encoder1Reading >> 0) & 0xFF;
  canMsg1.data[4] = (rate >> 16) & 0xFF;
  canMsg1.data[5] = (rate >> 8) & 0xFF;
  canMsg1.data[6] = (rate >> 0) & 0xFF;
  canMsg1.data[7] = can_cksum (canMsg1.data, 7, 0x230); //Toyota CAN CHECKSUM

  canMsg2.can_id  = 0x220;
  canMsg2.can_dlc = 8;
  canMsg2.data[0] = 0x0E;
  canMsg2.data[1] = 0x00;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0x08;
  canMsg2.data[4] = 0x01;
  canMsg2.data[5] = 0x00;
  canMsg2.data[6] = 0x00;
  canMsg2.data[7] = 0xA0;

  mcp2515.sendMessage(&canMsg1);
  //mcp2515.sendMessage(&canMsg2); //Only send message 1. Reserve for future use!

  //Serial.println(canMsg1.data[4]);
  
  delay(10);

}

//TOYOTA CAN CHECKSUM
int can_cksum (uint8_t *dat, uint8_t len, uint16_t addr) {
  uint8_t checksum = 0;
  checksum = ((addr & 0xFF00) >> 8) + (addr & 0x00FF) + len + 1;
  //uint16_t temp_msg = msg;
  for (int ii = 0; ii < len; ii++) {
    checksum += (dat[ii]);
  }
  return checksum;
}
