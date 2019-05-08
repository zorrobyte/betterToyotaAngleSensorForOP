# CAN Example
This example shows how to use the CAN port on the CAN485 board.

## Description
The transmitter node transmits a test packet over the CAN port every 500ms. The receiver passes anything received data to the serial port.

## Setup
- Setup as shown:
![CAN Example Setup](https://raw.githubusercontent.com/Atlantis-Specialist-Technologies/ast-arduino-boards/master/docs/_images/CAN-annotated.png)
- Flash the transmitter: [CAN Transmitter Sketch](https://github.com/Atlantis-Specialist-Technologies/AST_CanLib/blob/master/examples/CAN_Transmitter/CAN_Transmitter.ino "CAN Transmitter Sketch")
- Flash the Receiver: [CAN Receiver Sketch](https://github.com/Atlantis-Specialist-Technologies/AST_CanLib/blob/master/examples/CAN_Receiver/CAN_Receiver.ino "CAN Receiver Sketch")
- Connect the FTDI port of the receiver to a PC.
## Use
- Open a serial monitor for the receiver node.
- Observe the test data being received.
