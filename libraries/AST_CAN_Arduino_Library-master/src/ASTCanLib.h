/**********************************************************************************
 * Created by Atlantis Specialist Technologies
 * by James Blakey-Milner, 1 Aug 2017.
 * Ported the library to the Arduino platform
 * Main header file to include the library
 * Note! this file is in early development
 * (alpha) and is likely to change without notice.
 **********************************************************************************/
 
#ifndef _CAN_LIBRARY_H_
#define _CAN_LIBRARY_H_

#include <Arduino.h>

extern "C"{
	#include <can_lib.h>
}

void canInit(long baud);
void clearBuffer(uint8_t *Buffer);

#endif