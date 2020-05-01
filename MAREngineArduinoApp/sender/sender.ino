#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
float X_out, Y_out, Z_out;

int whenPrint = 0;

RF24 radio(9, 10);
const byte address[6] = "00001";
float transmit[3];

LiquidCrystal_I2C lcd(0x27, 16, 2);

void print_lcd(float const& x, float const& y, float const& z) {
  if(whenPrint == 10) {
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
    whenPrint = 0;
  }

  whenPrint++;
}

void setup() {
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();

   if(!accel.begin()) {
      Serial.println("No ADXL345 sensor detected.");
      while(1);
   }

  radio.begin();
  radio.setAutoAck(1);               
  radio.enableAckPayload();         
  radio.setRetries(5,15);
  radio.openWritingPipe(address);
  radio.stopListening();
  
  delay(10);
}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);
  X_out = event.acceleration.x;
  Y_out = event.acceleration.y;
  Z_out = event.acceleration.z;

  print_lcd(X_out, Y_out, Z_out);

  transmit[0] = X_out;
  transmit[1] = Y_out;
  transmit[2] = Z_out;
  if(!radio.write(&transmit, sizeof(transmit))) {
    lcd.setCursor(0, 0);
    lcd.print("Sth wrong");
  }

  delay(10);
}
