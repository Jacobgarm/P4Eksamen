int c = 9;
int state = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(33, INPUT_PULLUP);
  pinMode(32, INPUT_PULL);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long spdx = analogRead(33);
  long spdy = analogRead(32);
  Serial.print(spdx);
  Serial.print(" ");
  Serial.println(spdy);
  if (spdx < 2000)
    digitalWrite(25,LOW);
  else if (spdx > 3000)
    digitalWrite(25,HIGH);
  if (spdy < 2000)
    digitalWrite(27,LOW);
  else if (spdy > 3000)
    digitalWrite(27,HIGH);
  for (int i = 0; i <10; i++) {
    delay(1);
    if (abs(spdx - 2300) > 600) {
      digitalWrite(26,LOW);
      //Serial.println("A");
    }
    if (abs(spdy - 2300) > 600)
      digitalWrite(14,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1);
    if (abs(spdx - 2300) > 600)
      digitalWrite(26,HIGH);
    if (abs(spdy - 2300) > 600)
      digitalWrite(14,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
  }
  //delayMicroseconds((int)(1000/abs(spd)));
}

//100 steps = 2 cm
//300 steps = 6 cm
