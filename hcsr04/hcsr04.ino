#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trig = 5;
const int echo = 6;
long duration;
double distance;

void setup() {
  lcd.init();
  lcd.begin(16,2);
  
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034/2;
  Serial.println(distance);
  delay(2000);

  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distance, 4);
  lcd.print(" cm");
  delay(10);
}
