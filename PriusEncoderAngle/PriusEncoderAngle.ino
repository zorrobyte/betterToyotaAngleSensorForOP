#include <Encoder_Buffer.h>

#include <ASTCanLib.h>
#include <config.h>
#include <can_drv.h>
#include <can_compiler.h>
#include <can_lib.h>
#include <at90can_drv.h>

void setup() {
  // put your setup code here, to run once:
  
//init CAN thingy

//init Encoder thingy
}

void loop() {
  // put your main code here, to run repeatedly:

//Read steering angle (angle, fraction 1/15th) from Toyota CAN bus and store it to a var
//set the encoder current angle as angle from OEM sensor
//Read encoder angles and spam CAN bus with STEER_ANGLE

}
