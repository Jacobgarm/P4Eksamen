#include <Stepper.h>

const int stepsPerRevolution = 100;

Stepper stepLeft(stepsPerRevolution, 8, 9, 10, 11);
Stepper stepRight(stepsPerRevolution, 8, 9, 10, 11);

class Turtle {
  private:
    int angle;
    int x;
    int y;

  public:
    Turtle (int x, int y) {
      this->x = x;
      this->y = y;
      this->angle = 0;
      init();
    }

    void init() {

    }

    void turn(int angle) {
      this->angle += angle;
    }

    void move(int dist) {
      this->x;
      this->y;
    }
};

Turtle turt(10,10);

void setup() {
  // put your setup code here, to run once:

} 

void loop() {
  // put your main code here, to run repeatedly:

}
