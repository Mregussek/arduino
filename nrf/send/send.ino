//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//create an RF24 object
RF24 radio(9, 10);  // CE, CSN
LiquidCrystal_I2C lcd(0x27, 16, 2);

//address through which two modules communicate.
const byte address[6] = "00001";
int i = 0;

void setup()
{  // LCD Setup
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{
  bool result = radio.isChipConnected();
  lcd.setCursor(15, 0);
  lcd.print(result);
  
  //Send message to receiver
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  lcd.setCursor(0, 1);
  lcd.print(++i);
  
  delay(1000);
}
