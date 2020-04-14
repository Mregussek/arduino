#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>  
#include "RF24.h" 

LiquidCrystal_I2C lcd(0x27, 16, 2);
RF24 myRadio (7, 8); 

struct package {
  int id = 0;
  float temperature = 0.0;
  char text[100] ="empty";
};

const byte address[6] = "00001";
typedef struct package Package;
Package data;

void setup()  {
  // LCD Setup
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  
  Serial.begin(115200);
  delay(1000);

  myRadio.begin(); 
  myRadio.openReadingPipe(0, address);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.startListening();
}

void loop() {
  bool result = myRadio.isChipConnected();
  lcd.setCursor(15, 0);
  lcd.print(result);
  
  if ( myRadio.available() ) {
    while( myRadio.available() ) myRadio.read( &data, sizeof(data) );
    //Serial.print("\nPackage:");
    //Serial.print(data.id);
    //Serial.print("\n");
    //Serial.println(data.temperature);
    //Serial.println(data.text);

    lcd.setCursor(0, 0);
    lcd.print(data.id);
    lcd.setCursor(0, 1);
    lcd.print(data.temperature);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Data not found");
  }
}
