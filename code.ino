#include <ShiftRegister74HC595.h>

// Pin Definitions
int triggerPin = 2;
int echoPin = 3;
int buzzerPin = 4;
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

ShiftRegister74HC595 sr(latchPin, clockPin, dataPin);
int distance;

void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  sr.clear();
  sr.write(0);
  sr.commit();
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  distance = pulseIn(echoPin, HIGH);
  distance = distance / 58;
  
  if (distance >= 40) {
    sr.clear();
    sr.write(0);
    sr.commit();
  } else if (distance >= 35 && distance < 40) {
    sr.clear();
    sr.write(1);
    sr.commit();
  } else if (distance >= 30 && distance < 35) {
    sr.clear();
    sr.write(3);
    sr.commit();
  } else if (distance >= 25 && distance < 30) {
    sr.clear();
    sr.write(7);
    sr.commit();
  } else if (distance >= 20 && distance < 25) {
    sr.clear();
    sr.write(15);
    sr.commit();
  } else if (distance >= 15 && distance < 20) {
    sr.clear();
    sr.write(31);
    sr.commit();
  } else if (distance >= 10 && distance < 15) {
    sr.clear();
    sr.write(63);
    sr.commit();
  } else {
    sr.clear();
    sr.write(127);
    sr.commit();
  }
  
  if (distance < 10) {
    tone(buzzerPin, 1000, 100);
    delay(100);
    noTone(buzzerPin);
    delay(100);
  } else if (distance >= 10 && distance < 20) {
    tone(buzzerPin, 800, 100);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  } else {
    noTone(buzzerPin);
  }
}
