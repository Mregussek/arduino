#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

RF24 radio(9, 10);
const byte address[6] = "00001";
float recv[3];

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int r = 5;
const int g = 6;
const int b = 7;

void print_lcd(float const& x, float const& y, float const& z) {
  lcd.clear();
  lcd.setCursor(15, 0);
  lcd.print(radio.isChipConnected());
  
  lcd.setCursor(0, 0);
  lcd.print("X");
  lcd.setCursor(2, 0);
  lcd.print(x);
  lcd.setCursor(0, 1);
  lcd.print("Y");
  lcd.setCursor(2, 1);
  lcd.print(y);
  lcd.setCursor(8, 1);
  lcd.print("Z");
  lcd.setCursor(10, 1);
  lcd.print(z);
}

void handle_coordinates(float const& x, float const& y, float const& z) {
  if(x < -0.75) color(255, 0, 0);
  else if(x > 0.75) color(0, 255, 0);
  else color(0, 0, 255);
}

void color(int&& red, int&& green, int&& blue) {
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  
  radio.begin();
  radio.setAutoAck(1);             
  radio.enableAckPayload();       
  radio.setRetries(5,15);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  while(radio.available()) {
    radio.read(&recv, sizeof(recv));
  }

  print_lcd(recv[0], recv[1], recv[2]);
  handle_coordinates(recv[0], recv[1], recv[2]);
  
  delay(40);
}
