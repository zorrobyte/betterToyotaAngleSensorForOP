#include <Encoder_Buffer.h>

#include <ASTCanLib.h>
#include <config.h>
#include <can_drv.h>
#include <can_compiler.h>
#include <can_lib.h>
#include <at90can_drv.h>

//init Encoder thingy
#define EncoderCS1 8 //TODO: Set Pin!
long encoder1Reading = 0;
Encoder_Buffer Encoder1(EncoderCS1);

//init CAN thingy
#define MESSAGE_ID        256       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

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
  Serial.println(encoder1Reading);
  //Encoder1.clearEncoderCount();// Clear Encoder
  //Will be a number like 0, -13876, 13876, 7553839

//CAN thingy
  //  load data into tx buffer
  for (int i=0; i<8; i++){
    txBuffer[i] = sendData[i];
  }
  // Setup CAN packet.
  txMsg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  txMsg.id.ext   = MESSAGE_ID;        // Set message ID
  txMsg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  txMsg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit
  
  // Send command to the CAN port controller
  txMsg.cmd = CMD_TX_DATA;       // send message
  // Wait for the command to be accepted by the controller
  while(can_cmd(&txMsg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&txMsg) == CAN_STATUS_NOT_COMPLETED);
  // Transmit is now complete. Wait a bit and loop
  delay(500);
}

}
