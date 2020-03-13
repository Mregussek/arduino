
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11
#include "libraries/7seg.cpp"

// RGB LED
int bluePIN = 4;
int greenPIN = 5;
int redPIN = 6;

// BUTTON
int button = 2;

// FOTORESISTOR
int fotoA0 = A0;
int led = 3;
int limit = 800;

// DHT11 Sensor lib
int DHTpin = A5;
DHT dht(DHTpin, DHTTYPE);

// 7SEG 4 Digits
/* int segA and others declared in 7seg.cpp */
/* int digit1 and others also */


void color(int r, int g, int b); // set color on RGB diode
void lighting(); // checks lighting level and set diode to specific state
void temp_hum(); // checks temperature and humidity
void lightNumber(int numberToDisplay); // writes which segments must light to see specific number

void setup() {
  Serial.begin(9600);
  
  pinMode(bluePIN, OUTPUT);
  pinMode(greenPIN, OUTPUT);
  pinMode(redPIN, OUTPUT);
  pinMode(led, OUTPUT);
  
  pinMode(button, INPUT);
  pinMode(fotoA0, INPUT);
  
  dht.begin();

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
}

void loop() {
  lighting();
  temp_hum();
}

void color(int r, int g, int b) {
  analogWrite(redPIN, r);
  analogWrite(bluePIN, b);
  analogWrite(greenPIN, g);
}

void lighting() {
  int state = digitalRead(button);
  int val = analogRead(fotoA0);
  Serial.println(val);

  if (val <= limit)
  {
    digitalWrite(led, HIGH);
     
    if (state == HIGH)
      color(0, 255, 0);
    else
      color(255, 0, 0);
  }
  else
  {
    digitalWrite(led, LOW);
    color(0, 0, 255);
  }
}

void temp_hum() {
  int del = 5; // delay
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp))
    return;

  clearLEDs();
  pickDigit(0);
  lightNumber(hum / 10);
  delay(del);

  clearLEDs();
  pickDigit(1);
  lightNumber(hum % 10);
  delay(del);

  clearLEDs();
  pickDigit(2);
  lightNumber(temp / 10);
  delay(del);

  clearLEDs();
  pickDigit(3);
  lightNumber(temp % 10);
  delay(del);
}
