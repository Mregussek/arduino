#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int ADXL345 = 0x53;
float X_out, Y_out, Z_out;  // Outputs
LiquidCrystal_I2C lcd(0x27, 16, 2);

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
  
  lcd.setCursor(0, 0);
  lcd.print("X");
  lcd.setCursor(2, 0);
  lcd.print(X_out);
  lcd.setCursor(0, 1);
  lcd.print("Y");
  lcd.setCursor(2, 1);
  lcd.print(Y_out);
  lcd.setCursor(8, 1);
  lcd.print("Z");
  lcd.setCursor(10, 1);
  lcd.print(Z_out);
  //lcd.setCursor(15, 0);
}
