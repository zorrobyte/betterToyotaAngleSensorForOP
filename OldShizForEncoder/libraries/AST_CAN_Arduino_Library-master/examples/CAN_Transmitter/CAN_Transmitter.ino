/*
 * CAN port receiver example
 * Repeatedly transmits an array of test data to the CAN port
 */

#include <ASTCanLib.h>  

#define MESSAGE_ID        256       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

// CAN message object
st_cmd_t txMsg;

// Array of test data to send
const uint8_t sendData[8] = {0,10,20,40,80,100,120,127};
// Transmit buffer
uint8_t txBuffer[8] = {};

void setup() {
  canInit(500000);                  // Initialise CAN port. must be before Serial.begin
  Serial.begin(1000000);             // start serial port
  txMsg.pt_data = &txBuffer[0];      // reference message data to transmit buffer
}

void loop() {
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
