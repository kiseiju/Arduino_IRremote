#include <boards.h>
#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include <ble_shield.h>
#include <services.h>
#include <IRremote.h>
//#include <aJSON.h>
IRsend irsend;

unsigned int HDMI1 [67]={8900,4450,550,550,500,650,500,550,550,600,500,600,550,550,600,500,600,550,500,1700,500,1700,550,1700,500,1700,500,1750,500,1700,550,1700,500,1700,550,550,500,650,500,1700,500,600,550,550,550,600,500,600,500,600,550,1700,500,1700,500,650,500,1700,500,1700,550,1700,500,1700,500,1750,500};
unsigned int HDMI2 [67]={8900,4450,500,600,500,600,500,600,550,600,500,600,500,600,500,600,500,650,500,1700,500,1700,550,1700,500,1700,500,1700,550,1700,550,1700,500,1700,550,600,500,600,500,600,500,1750,500,600,500,600,500,600,500,600,550,1700,500,1700,500,1700,550,600,500,1700,550,1700,500,1700,500,1700,550};
unsigned int HDMI3 [67]={8850,4450,550,600,500,600,500,600,500,600,500,650,500,550,550,600,500,600,550,1650,500,1750,550,1650,550,1700,500,1700,550,1700,500,1750,450,1750,500,600,500,1700,550,600,500,1700,550,550,500,650,500,600,500,600,500,1700,550,600,500,1700,500,600,500,1750,500,1700,500,1750,500,1700,500};

void setup()
{
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();
  
  ble_begin();
  
  Serial.begin(57600);
}

char buf[16] = {0};
int len = 0; 
void loop()
{
  while (ble_available()){
    unsigned char c = ble_read();
    //Serial.write(c);
    //Eric Wang
    buf[len++] = c;
  }
  if (len != 0) {
    
    if (len >= 3) {
      Serial.println(buf);
      if (buf[0] == 'S') {
//        Serial.println(buf);
//        Serial.println(&buf[2]);
        toSony(&buf[2]);
      }
      else if (buf[0] == 'N') {
        Serial.println(&buf[2]);
        toNEC(&buf[2]);
      }
      else if (buf[0] == 'B') {
        Serial.println(&buf[2]);
        delay(100);
        toiBuffalo(buf[2]);
      }
    }
    
    
    //Serial.println(buf);
    //Serial.println(len); 
//    String a = String(buf);
//    String a;
//    a = String(buf);
//    Serial.println(a);
//    String b = String(buf).substring(2,String(buf).length());
//    Serial.println(b);
//    if (a == "S")  
//      toSony(b);
//    if (a == "N")  
//      toNEC(b);
//    if (a == "B")  
//      toiBuffalo(b);
  }

  len = 0;
  
  ble_do_events();
}

void toSony(char* x){
//  unsigned long v = 0x0;
  Serial.println("SONY!!");
//  Serial.println(x);
//  long unsigned int b = strtoul(x, 0, 16);

  for (int i = 0; i < 3; i++) {
  irsend.sendSony(strtoul(x, 0, 16), 12); // Sony TV power code
  delay(40);
  }
}

void toNEC(char* x){
//  unsigned long v = 0x0;
  Serial.println("NEC!!");
  Serial.println(x);
//  long unsigned int b = strtoul(x, 0, 16);
  irsend.sendNEC(strtoul(x, 0, 16), 32); // Sony TV power code
}

void toRaw(unsigned int buf[]){
  irsend.sendRaw(HDMI1, 67, 38);
}

void toiBuffalo(char x){
  int b = atoi(&x); 
  Serial.println(b);
  switch (b) {
    case 1:
      Serial.println("B1!!");
      toRaw(HDMI1);
      break;
    case 2:
      Serial.println("B2!!");
      toRaw(HDMI2);
      break;
    case 3:
      Serial.println("B3!!");
      toRaw(HDMI3);
      break;
  }
}
//
//void toBBtv(int x){
//  int result;
//}
