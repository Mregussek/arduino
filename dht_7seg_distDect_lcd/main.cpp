#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TM1637Display.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define CLK 2
#define DIO 3
#define DHTPIN A0
#define DHTTYPE DHT11
#define TRIG 5
#define ECHO 6
#define LED 8
#define SOUND A4

int temperature_celsius;
int temperature_fahrenheit;
long duration;
double distance;
int mic_read;
int mic_treshold = 75;

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

void setup() {
  // LCD Setup
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();

  // Distance Detector Setup
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // 7seg Setup
  display.setBrightness(0);
  display.clear();

  // DHT Setup
  dht.begin();

  // MIC Setup
  pinMode(LED, OUTPUT);
  pinMode(SOUND, INPUT);
  
  delay(2000);
}

void loop() {
  // Get temperature and display it on 7seg
  temperature_celsius = dht.readTemperature();
  temperature_fahrenheit = dht.readTemperature(true);
  display.showNumberDec(temperature_celsius, false, 2, 0);
  display.setSegments(celsius, 2, 2);

  // Read distance and calculate it
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034/2;

  // Display distance on LCD screen
  lcd.setCursor(0,0);
  lcd.print("Dst: ");
  lcd.print(distance, 3);
  lcd.print(" cm");
  delay(500);
  
  // Check if mic got sth
  mic_read = analogRead(SOUND);
  if(mic_read >= mic_treshold) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
  lcd.setCursor(0,1);
  lcd.print("Noise: ");
  lcd.print(mic_read);
  lcd.print(" db");

  delay(1500);
}
