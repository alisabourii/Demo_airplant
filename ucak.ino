#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h> 
#include <SPI.h>
#include <Servo.h>

Enrf24 nRF(9,10, 8);   
const byte alici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 };

Servo srv;

void setup() {
    SPI.begin(); 
    SPI.setDataMode(SPI_MODE0); 
    SPI.setBitOrder(MSBFIRST); 
    nRF.begin(1000000,124); 
    nRF.setRXaddress(alici_adresi); 
    nRF.enableRX();  
  for(int i=3; i<=4; i++)
    pinMode(i, OUTPUT);
  srv.attach(2);
  for(int i=0; i<=180; i++){
    srv.write(i);
    delay(10);}
  srv.write(90);  
  
}

void loop() {
  char gelen_bilgi[33]; 
  int bilgi=0; 

  if (nRF.read(gelen_bilgi))  
  {
    bilgi = atoi(gelen_bilgi);
    
     Serial.println(gelen_bilgi[0]);   
    
    if(gelen_bilgi[0]=='F')   {
      digitalWrite(3,1);
      digitalWrite(4,0);}

     if(gelen_bilgi[0]=='B')   {
      digitalWrite(3,0);
      digitalWrite(4,1);}

    else if(gelen_bilgi[0]=='R')
        srv.write(100);

    else if(gelen_bilgi[0]=='L')
        srv.write(50);

    else if(gelen_bilgi[0]=='M'){
        srv.write(90);
        digitalWrite(3,0);
        digitalWrite(4,0);

    }
  }
}
 