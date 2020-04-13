#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int btn1 = 2;
const int btn2 = 3;
const int r = 12;
const int g = 11;
const int b = 10;

int state1;
int state2;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void color(int red, int green, int blue) {
  analogWrite(r, red);
  analogWrite(g, green);
  analogWrite(b, blue);
}

void setup() {
  // LCD Setup
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();

  Serial.begin(9600);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}
void loop() {
  state1 = digitalRead(btn1);
  state2 = digitalRead(btn2);

  lcd.clear();
  if(state1 == LOW && state2 == LOW) {
    color(255, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("1. Pressed");
    lcd.setCursor(0, 1);
    lcd.print("2. Pressed");
  } else if(state1 == HIGH && state2 == LOW) {
    color(0, 255, 0);
    lcd.setCursor(0, 0);
    lcd.print("1. Click please");
    lcd.setCursor(0, 1);
    lcd.print("2. Pressed");
  } else if(state1 == LOW && state2 == HIGH) {
    color(0, 0, 255);
    lcd.setCursor(0, 0);
    lcd.print("1. Pressed");
    lcd.setCursor(0, 1);
    lcd.print("2. Click please");
  } else {
    color(0, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("1. Click please");
    lcd.setCursor(0, 1);
    lcd.print("2. Click please");
  }

  delay(100);
}
