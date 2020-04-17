#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int ADXL345 = 0x53;
float X_out, Y_out, Z_out;

RF24 radio(9, 10);
const byte address[6] = "00001";
float transmit[3];

LiquidCrystal_I2C lcd(0x27, 16, 2);

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

void setup() {
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();

  Serial.begin(9600); 
  
  Wire.begin();
  Wire.beginTransmission(ADXL345); 
  Wire.write(0x2D); 
  Wire.write(8);
  Wire.endTransmission();

  radio.begin();
  radio.setAutoAck(1);               
  radio.enableAckPayload();         
  radio.setRetries(5,15);
  radio.openWritingPipe(address);
  radio.stopListening();
  
  delay(10);
}

void loop() {
  

  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);
  
  X_out = ( Wire.read()| Wire.read() << 8);
  X_out = X_out/256;
  Y_out = ( Wire.read()| Wire.read() << 8);
  Y_out = Y_out/256;
  Z_out = ( Wire.read()| Wire.read() << 8);
  Z_out = Z_out/256;

  print_lcd(X_out, Y_out, Z_out);

  transmit[0] = X_out;
  transmit[1] = Y_out;
  transmit[2] = Z_out;
  if(!radio.write(&transmit, sizeof(transmit))) {
    lcd.setCursor(0, 0);
    lcd.print("Sth wrong");
  }

  delay(400);
}
