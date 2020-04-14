//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN
LiquidCrystal_I2C lcd(0x27, 16, 2);

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{
  while (!Serial);
    Serial.begin(9600);

    // LCD Setup
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  bool result = radio.isChipConnected();
  lcd.setCursor(15, 0);
  lcd.print(result);
  
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
    lcd.setCursor(0, 1);
    lcd.print(text);
  }
}
