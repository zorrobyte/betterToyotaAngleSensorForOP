#include <can.h>
#include <mcp2515.h>
#include <ams_as5048b.h>

//CAN
struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

//ANGSENSOR
#define U_RAW 1
#define U_TRN 2
#define U_DEG 3
#define U_RAD 4
#define U_GRAD 5
#define U_MOA 6
#define U_SOA 7
#define U_MILNATO 8
#define U_MILSE 9
#define U_MILRU 10
AMS_AS5048B angsensor;
int32_t encoder1Reading = 0;

void setup() {
  
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();

  //INIT CAN
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //8Mhz oscillator
  mcp2515.setNormalMode();
  
  //INIT ANGSENSOR
  angsensor.begin();
  angsensor.setClockWise(true);
  angsensor.setZeroReg(); //consider the current pos as zero
}

void loop() {

  //ANGSENSOR
  encoder1Reading = angsensor.angleR(U_DEG, true); //READ the ANGSENSOR
  Serial.println(angsensor.angleR(U_DEG, true));

  //CAN
  canMsg1.can_id  = 0x23;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = (encoder1Reading >> 16) & 0xFF; //Bitshift the ANGSENSOR (24 bit, Cabana errors with 32 bit)
  canMsg1.data[1] = (encoder1Reading >> 8) & 0xFF;
  canMsg1.data[2] = (encoder1Reading >> 0) & 0xFF;
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
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

  //Serial.println("Messages sent");
  
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
