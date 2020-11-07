#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// 7 and 8 are the modules of CE and CSN
RF24 radio(7,8);
const byte address[6] = "00001";

int switch_pin_propellor = 0;
int x_propellor = 1;
int y_propellor = 2;

const int error = 5;

// 'Z' is just a trash variable
char prev_propellor_message = 'Z';

void sendPropellorMessage(char p_p){
  const char text[3] = "pU";
  radio.write(&text, sizeof(text));
  delay(1000);
}

char joystick_translator(int y){
  if(y < 500 - error){
    return 'U';  
  }else if(y > 500 + error){
    return 'D';  
  }else{
    return 'C';
  }
}

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(switch_pin_propellor, INPUT);
  digitalWrite(switch_pin_propellor, HIGH);
}

void loop() {
  int yp = analogRead(y_propellor);

  char prop_pos = joystick_translator(yp);

  if(prev_propellor_message != prop_pos){
    sendPropellorMessage(prop_pos);  
  }
}
