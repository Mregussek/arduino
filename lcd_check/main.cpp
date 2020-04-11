#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h> // dolaczenie pobranej biblioteki I2C dla LCD

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
}
void loop() {
}
