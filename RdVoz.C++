/**
******************************************************************************
* @file VOZ.ino
* @author desarrollo de software
******************************************************************************
******************************************************************************
* @section HISTORY

2022/09/05 Initial version.
*/

#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**
Connection
Arduino VoiceRecognitionModule
2 -------> TX
3 -------> RX
*/
VR myVR(2,3); // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

int ledLlave = 13;
int ledSala = 12;
int ledCocina = 11;
int ledCuarto = 10;

#define llave (0)
#define sala (1)
#define cocina (2)
#define cuarto (3)
#define encender (5)
#define apagar (6)
len --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
int i;
for(i=0; i<len; i++){
if(buf[i]>0x19 && buf[i]<0x7F){
Serial.write(buf[i]);
}
else{
Serial.print("[");
Serial.print(buf[i], HEX);
Serial.print("]");
}
}
}

/**
@brief Print signature, if the character is invisible,
print hexible value instead.
@param buf --> VR module return value when voice is recognized.
buf[0] --> Group mode(FF: None Group, 0x8n: User, 0x0n:System
buf[1] --> number of record which is recognized.
buf[2] --> Recognizer index(position) value of the recognized record.
buf[3] --> Signature length
buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
Serial.println("VR Index\tGroup\tRecordNum\tSignature");

Serial.print(buf[2], DEC);
Serial.print("\t\t");

if(buf[0] == 0xFF){
Serial.print("NONE");
}