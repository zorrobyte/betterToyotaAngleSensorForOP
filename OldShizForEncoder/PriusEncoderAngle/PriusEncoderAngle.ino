#include <Encoder_Buffer.h>

#include <ASTCanLib.h>
#include <config.h>
#include <can_drv.h>
#include <can_compiler.h>
#include <can_lib.h>
#include <at90can_drv.h>

//init Encoder thingy
#define EncoderCS1 7 //TODO: Set Pin!
int32_t encoder1Reading = 0;
Encoder_Buffer Encoder1(EncoderCS1);

//init CAN thingy
#define MESSAGE_ID        0x23       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

// CAN message object
st_cmd_t txMsg;

// Array of test data to send
// Transmit buffer
uint8_t txBuffer[8] = {};

void setup() {
  // put your setup code here, to run once:
  //encoder thingy
  Serial.begin(9600);
  SPI.begin();
  Encoder1.initEncoder();
  //CAN thingy
  canInit(500000);                  // Initialise CAN port. must be before Serial.begin
  //Serial.begin(1000000);             // start serial port
  txMsg.pt_data = &txBuffer[0];      // reference message data to transmit buffer
}

void loop() {
  // put your main code here, to run repeatedly:

  //encoder thingy
  encoder1Reading = Encoder1.readEncoder();//Read Encoder
  //Encoder1.clearEncoderCount();// Clear Encoder

  //CAN thingy
  //  load data into tx buffer
  txBuffer[0] = (encoder1Reading >> 16) & 0xFF;
  txBuffer[1] = (encoder1Reading >> 8) & 0xFF;
  txBuffer[2] = (encoder1Reading >> 0) & 0xFF;
  txBuffer[3] = 0x0;
  //txBuffer[2] = (rate >> 8) & 0xFF;
  //txBuffer[3] = (rate >> 0) & 0xFF;
  txBuffer[4] = 0x0;
  txBuffer[5] = 0x0;
  txBuffer[6] = 0x0;
  txBuffer[7] = can_cksum (txBuffer, 7, 0x23);
  //txBuffer[7] = 0x0;
  //txBuffer[i] = sendData[i];
  // Setup CAN packet.
  txMsg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  txMsg.id.ext   = MESSAGE_ID;        // Set message ID
  txMsg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  txMsg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit
  //Serial.println(txBuffer[1]);

  // Send command to the CAN port controller
  txMsg.cmd = CMD_TX_DATA;       // send message
  // Wait for the command to be accepted by the controller
  while (can_cmd(&txMsg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while (can_get_status(&txMsg) == CAN_STATUS_NOT_COMPLETED);
  // Transmit is now complete. Wait a bit and loop
  delay(11.363636363636);
  //(88Hz)delay so it doesn't DOS the CAN BUS https://discordapp.com/channels/469524606043160576/574796986822295569/587308808938717185
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
