#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int button = 2;
const int led = 3;

int buttonState;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // LCD Setup
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}
void loop() {
  buttonState = digitalRead(button);

  if(buttonState == LOW) {
    digitalWrite(led, HIGH);
    lcd.clear();
    lcd.print("Button Pressed");
  } else {
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.print("Press the button!");
  }
  
  delay(100);
}
