#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte address[6] = "00001";

void setup() {
  Serial.begin(19200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if(radio.available()){
    Serial.println("Received something!");
    char text[10] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }else{
  }
}
