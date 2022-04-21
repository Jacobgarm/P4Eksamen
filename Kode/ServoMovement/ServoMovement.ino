
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(12, 1000, 2000); // attaches the servo on pin 12 to the servo object

  Serial.begin(115200);

  resetPosition();

  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
   pinMode(35, INPUT_PULLUP);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
}

void loop() {

  ned(0, 100);

  op(180, 100);

  long spdx = analogRead(33);
  long spdy = analogRead(32);
  Serial.print(spdx);
  Serial.print(" ");
  Serial.println(spdy);
  if (spdx < 2000)
    digitalWrite(26,LOW);
  else if (spdx > 3000)
    digitalWrite(26,HIGH);
  if (spdy < 2000)
    digitalWrite(14,LOW);
  else if (spdy > 3000)
    digitalWrite(14,HIGH);
  for (int i = 0; i <10; i++) {
    delay(1);
    if (abs(spdx - 2300) > 600) {
      digitalWrite(25,LOW);
      //Serial.println("A");
    }
    if (abs(spdy - 2300) > 600)
      digitalWrite(27,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1);
    if (abs(spdx - 2300) > 600)
      digitalWrite(25,HIGH);
    if (abs(spdy - 2300) > 600)
      digitalWrite(27,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println(digitalRead(16));
    Serial.println(digitalRead(17));
  }
}
