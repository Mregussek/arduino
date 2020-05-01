#define BAUD 9600
#define DELAY_TIME 10

float i = 0.0;

void sendOnSP(float x, char&& whichVal) {
  char spBuff[16];
  char xBuf[16];
  dtostrf(x, 3, 2, xBuf);
  if(whichVal == 'x') snprintf(spBuff, sizeof(spBuff), "#x--%s", xBuf);
  else if(whichVal == 'y') snprintf(spBuff, sizeof(spBuff), "#y--%s", xBuf);
  else snprintf(spBuff, sizeof(spBuff), "#z--%s", xBuf);
  Serial.println(spBuff);
}

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  sendOnSP(i, 'x');
  sendOnSP(i, 'y');
  sendOnSP(i, 'z');
  i += 3.0;
  delay(DELAY_TIME);
}
