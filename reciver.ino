#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial Mp3_Serial(10, 11);

int Volume = 65; //Set volume from 0-100, I recommend 65;
int Track_Length = 2.1; //In seconds
int Led = 13;
int i = 0;

DFRobotDFPlayerMini Mp3_Player;


RF24 radio(7, 8);
const byte address[6] = "00001";

bool Door_Bell_Pressed = false;

void setup() {
  Mp3_Serial.begin(9600);
  Mp3_Player.begin(Mp3_Serial);
  Mp3_Player.volume(Volume / 3.33333333);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(Led, OUTPUT);
}
void loop() {
  if (radio.available()) {
    radio.read(&Door_Bell_Pressed, sizeof(Door_Bell_Pressed));
    radio.read(&i, sizeof(i));
  }

  if (Door_Bell_Pressed == true && i == 0) {
    Play();
  }
}

void Play() {
  Mp3_Player.play(1);
  delay(Track_Length * 1000);
  i = 1;
}
