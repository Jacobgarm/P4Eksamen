
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
