# betterToyotaAngleSensorForOP

The project aims to provide an improved angle sensor setup for Toyota vehicles compatible with OpenPilot. This involves installing a magnetic encoder sensor for more accurate angle readings, supplemented by necessary electronics and firmware.

## Components

Below is a list of components needed for this project:

### 1. Magnetic Encoder (AS5047P)
- **Evaluation Board (AS5047P)**: Includes the magnet necessary for sensor calibration.
  - Purchase: [Digikey](https://www.digikey.com/product-detail/en/ams/AS5047P-TS_EK_AB/AS5047P-TS_EK_AB-ND/5452344)
  - [Datasheet](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf)
  - [Arduino Library](http://www.massmind.org/techref/io/sensor/pos/enc/ENC2-47P-Arduino.htm) (Default 4096 PPR)

### 2. Microcontroller and CAN Interface
- **Arduino**: Compatible with most versions (e.g., [this one](https://www.amazon.com/gp/product/B0713XK923/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1))
- **CAN Board**: MCP2515 module for CAN communication.
  - Purchase: [Amazon](https://www.amazon.com/HiLetgo-MCP2515-TJA1050-Receiver-Arduino/dp/B01D0WSEWU)
  - Library: [GitHub - arduino-mcp2515](https://github.com/autowp/arduino-mcp2515)

### 3. Encoder Buffer
- **LS7366R Quadrature Encoder Buffer**: Enables precise angle tracking.
  - Purchase: [SuperDroid Robots](https://www.superdroidrobots.com/shop/item.aspx/single-ls7366r-quadrature-encoder-buffer/2397/)
  - Library: [GitHub - Encoder Buffer Library](https://github.com/SuperDroidRobots/Encoder-Buffer-Library)

### 4. Additional Hardware
- **M3 Flat-Cap Screws**: Stainless steel, non-ferrous recommended.
  - Purchase: [Amazon](https://www.amazon.com/iExcell-Stainless-Internal-Drives-Screws/dp/B07D686M7N)
- **3D Printed Components**: Necessary parts for mounting and alignment.
  - Files: [Fusion 360](https://a360.co/2X2c5dA)

### 5. Optional Items
- **Erich’s Magnet Holder**: No permanent modifications required for installation. [Join Discord](https://discord.com/channels/469524606043160576/524327905937850394/637664746539319305) for more information.
- **BOM (Bill of Materials)**: A supplementary [BOM on Google Sheets](https://docs.google.com/spreadsheets/d/1Pn6zGi96R18uo3hBh6kgpqTcffqMBHuL74cx0rIaKcA/edit?usp=sharing) to assist with sourcing components.

## Assembly Instructions

1. **Connections**:
   - Connect the CAN board and LS7366R to the Arduino.
   - Wire the AS5047P sensor to the LS7366R encoder buffer.

2. **Mechanical Setup**:
   - Extend the hole in the EPS motor shaft, if needed, and tap it to M3 size.
   - Align and attach the magnet holder to the cap.
   - Snap the AS5047P sensor into place and secure it with a small amount of superglue once functionality is confirmed.

3. **Software Configuration**:
   - Recalibrate your vehicle’s fingerprint and add the new signals to Cabana.
   - Adjust the angle offset within OpenPilot settings.
   
## Additional Resources

- DIY listing on OSHWLab: [OSHWLab Project](https://oshwlab.com/kata3/zss-final)
- [GitHub Discussion and Updates](https://discord.com/channels/469524606043160576/524327905937850394/637664746539319305)

## Acknowledgments

Special thanks to Erich and the community for providing valuable resources and feedback.
