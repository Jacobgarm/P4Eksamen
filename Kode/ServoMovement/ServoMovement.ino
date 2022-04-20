
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
}

void loop() {

  ned(0, 100);

  op(180, 100);
}
