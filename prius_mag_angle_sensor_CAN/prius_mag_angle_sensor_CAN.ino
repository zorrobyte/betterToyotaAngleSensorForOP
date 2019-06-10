#include <SPI.h>
#include <mcp2515.h>
#include <ams_as5048b.h>

//unit consts for as5048b
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

//min angle is 0, max is like 16357.00 or around for RAW. Wraps back around to 0 (unsigned)

struct can_frame canMsg1;
MCP2515 mcp2515(10);

//angle reading
int16_t encoder1Reading = 0;


void setup() {
  
  while (!Serial);
  Serial.begin(9600);
  SPI.begin();

  //init AMS_AS5048B object
  angsensor.begin();

  //consider the current position as zero
  angsensor.setZeroReg();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {

  //the angle sensor reading
  //Serial.print("Angle sensor raw : ");
  //Serial.println(angsensor.angleR(U_RAW, true));

  //set the encoder1reading to the angle
  encoder1Reading = angsensor.angleR(U_RAW, true);

  //the message
  canMsg1.can_id  = 0x23;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = (encoder1Reading >> 8) & 0xFF;
  canMsg1.data[1] = (encoder1Reading >> 0) & 0xFF;
  canMsg1.data[2] = 0x0;
  canMsg1.data[3] = 0x0;
  canMsg1.data[4] = 0x0;
  canMsg1.data[5] = 0x0;
  canMsg1.data[6] = 0x0;
  canMsg1.data[7] = 0x0;
  //canMsg1.data[7] = can_cksum (txBuffer, 7, 0x23); TODO: Implement This
  
  //send message
  mcp2515.sendMessage(&canMsg1);

  Serial.println(canMsg1.data[0]);
  Serial.println(canMsg1.data[1]);
  
  delay(100);

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
