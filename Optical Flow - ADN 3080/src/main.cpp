#include <Arduino.h>
#include <SPI.h>

void setup() {
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV64);    
  Serial.begin(9600);
  digitalWrite(SS, HIGH);
  delay(1000);
}

void loop() {
  digitalWrite(SS, LOW);
  Serial.println(SPI.transfer(0x0A), HEX);
  digitalWrite(SS, HIGH);
  delay(1000);
  digitalWrite(SS, LOW);
  Serial.println(SPI.transfer(0x3F), HEX);
  digitalWrite(SS, HIGH);
  delay(1000);
}