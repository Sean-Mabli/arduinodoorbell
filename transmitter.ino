#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

bool Door_Bell_Pressed = false;
int Button_Pin = 2;
int i = 0;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(Button_Pin, INPUT);
}
void loop() {
  if (digitalRead(Button_Pin) == LOW) {
    Door_Bell_Pressed = true;
  }
  else {
    Door_Bell_Pressed = false;
  }

  radio.write(&Door_Bell_Pressed, sizeof(Door_Bell_Pressed));
  radio.write(&i, sizeof(i));
}
