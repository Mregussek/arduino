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
bool shouldPrint = true;

void sendOnSP(float x, float y, float z) {
  char spBuff1[16];
  char xBuf[16];
  dtostrf(x, 3, 2, xBuf);
  snprintf(spBuff1, sizeof(spBuff1), "#x# %s ", xBuf);
  
  char spBuff2[16];
  char yBuf[16];
  dtostrf(y, 3, 2, yBuf);
  snprintf(spBuff2, sizeof(spBuff2), "#y# %s ", yBuf);
  
  char spBuff3[16];
  char zBuf[16];
  dtostrf(z, 3, 2, zBuf);
  snprintf(spBuff3, sizeof(spBuff3), "#z# %s", zBuf);

  char* buff = malloc(48);
  strcpy(buff, spBuff1);
  strcat(buff, spBuff2);
  strcat(buff, spBuff3);
  Serial.println(buff);
  free(buff);
}

void print_lcd(float const& x, float const& y, float const& z) {
  if(shouldPrint) {
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
    shouldPrint = false;
    return;
  }

  shouldPrint = true;
}

void handle_coordinates(float const& x, float const& y, float const& z) {
  if(y > 5.0f) color(255, 0, 0);
  else if(z < 0.2f) color(0, 255, 0);
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

  if(recv[0] && recv[1] && recv[2]) {
    sendOnSP(recv[0], recv[1], recv[2]);
    print_lcd(recv[0], recv[1], recv[2]);
    handle_coordinates(recv[0], recv[1], recv[2]);
  }
  
  delay(10);
}
