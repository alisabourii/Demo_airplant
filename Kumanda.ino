#include <Enrf24.h>
#include <nRF24L01.h>
#include <SPI.h>

Enrf24 nRF(9, 10, 8);  // CE , CSN/CS/SS , IRQ bacaklarının Arduino ile bağlantıları tanımlandı

// verici adresi tanımlandı aynı adres alıcıda da tanımlanmalıdır
const byte verici_adresi[] = { 0xDE, 0xAD, 0xBE, 0x0F, 0x01 };

void setup() {
  Serial.begin(9600);
  SPI.begin(); // SPI başlat
  SPI.setDataMode(SPI_MODE0); // SPI MODE0 seçildi, nrf24l01 MODE0 ile iletişim kurmaktadır
  SPI.setBitOrder(MSBFIRST); // bit sıralaması MSB'den LSB'ye doğru ayarlandı
  nRF.begin(1000000,124);  
  nRF.setTXaddress(verici_adresi); // verici adresi ayarlandı
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  //nRF.print("F"); 
  //nRF.flush(); 
  int sag_sol = analogRead(A1);
  int ileri_geri = analogRead(A0);

 if(ileri_geri > 350 && ileri_geri < 800){
    if(sag_sol < 350) {
        Serial.println("Sol");
        nRF.print("R"); 
        nRF.flush(); 
      }
    else if(sag_sol > 800){
        Serial.println("Sağ");
        nRF.print("L"); 
        nRF.flush(); 
      }
    else if(sag_sol > 350 && sag_sol <800 )
        Serial.println("Orta");
        nRF.print("M"); 
        nRF.flush(); 
    }
  else {
    if(ileri_geri < 350) {
        Serial.println("geri");
        nRF.print("B"); 
        nRF.flush(); 
      }
    else if(ileri_geri > 800){
        Serial.println("ileri");
        nRF.print("F"); 
        nRF.flush(); 
      }
  }
  delay(500);
}
