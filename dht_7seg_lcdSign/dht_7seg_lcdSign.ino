//LCD16x2 sterowany przez I2C Arduino

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11 
#define CLK 2
#define DIO 3
#define DHTPIN 4

int temperature_celsius;
int temperature_fahrenheit;

const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};

const uint8_t fahrenheit[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_E | SEG_F | SEG_G   // F
};

TM1637Display display = TM1637Display(CLK, DIO);

DHT dht = DHT(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  lcd.init();
  lcd.begin(16,2);
  
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Mateusz");
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Rzeczyca");

  display.setBrightness(0);
  display.clear();
  dht.begin();
  Serial.begin(9600);
  delay(2000);
}
void loop() {
  temperature_celsius = dht.readTemperature();
  temperature_fahrenheit = dht.readTemperature(true);
  Serial.println(temperature_celsius);
  Serial.println(temperature_fahrenheit);
  display.showNumberDec(temperature_celsius, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(2000);
  display.showNumberDec(temperature_fahrenheit, false, 2, 0);
  display.setSegments(fahrenheit, 2, 2);
  delay(2000);
}
