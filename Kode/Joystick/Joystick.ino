
#include <ESP32Servo.h>
int c = 9;
int state = LOW;
Servo myservo;  // create servo object to control a servo


//Hastighed mellem 90 og 180
void op(int hastighed, int tid) {
  if (hastighed >= 90 && hastighed <= 180) {
    myservo.write(hastighed);
    Serial.println("Op");
    delay(tid);
  }
}

//Hastighed mellem 0 og 90
void ned(int hastighed, int tid) {
  if (hastighed >= 0 && hastighed <= 90) {
    myservo.write(hastighed);
    Serial.println("Ned");
    delay(tid);
  }

}

void resetPosition() {
  Serial.println("Resetting");
  ned(50, 1000);
  op(180, 100);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
<<<<<<< HEAD
=======
   pinMode(35, INPUT_PULLUP);
>>>>>>> 0950fb2fc6336df14fbcb7763edb178bdcc9ae7f
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(12, 1000, 2000); // attaches the servo on pin 12 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
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
  }
  //delayMicroseconds((int)(1000/abs(spd)));

  if (digitalRead(35) == LOW) {
  ned(0, 100);

  op(180, 100);  
  }
}

//100 steps = 2 cm
//300 steps = 6 cm
