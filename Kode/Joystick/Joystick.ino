#include <Arduino_FreeRTOS.h>

#define VRX_PIN  A8 // Arduino pin connected to VRX pin
#define VRY_PIN  A9 // Arduino pin connected to VRY pin

//Pins for steppermotors
#define xStepPin 30
#define xDirPin 31

#define yStepPin 32
#define yDirPin 33

const int stepsPerRevolution = 200;

float xSpeed = 5;
float ySpeed = 5;
bool xForward = true;

void TaskXStep(void *pvParameters);
void TaskYStep(void *pvParameters);
void TaskInput(void *pvParameters);
//Pen state variable
bool penIsDown; 

void setup() {
  pinMode(xStepPin, OUTPUT);
  pinMode(yStepPin, OUTPUT);
  pinMode(xDirPin, OUTPUT);
  pinMode(yDirPin, OUTPUT);
  Serial.begin(9600);
  xTaskCreate(TaskXStep, "XStep", 128, NULL, 2, NULL);
  xTaskCreate(TaskYStep, "YStep", 128, NULL, 1, NULL);
  xTaskCreate(TaskInput, "Input", 128, NULL, 1, NULL);
}

void TaskInput(void *pvParameters) {
  for (;;) {
     //xSpeed = map(analogRead(VRX_PIN), 0, 1024, -10, 10);
     //ySpeed = map(analogRead(VRY_PIN), 0, 1024, -10, 10);
     vTaskDelay(10.0/portTICK_PERIOD_MS);
  }  
}

void TaskXStep(void *pvParameters) {
  for(;;){
    if (xSpeed < 0 && xForward) {
      xForward = false;
      digitalWrite(xDirPin, LOW);
    }
    else if (xSpeed > 0 && !xForward) {
      xForward = true;
      digitalWrite(xDirPin, HIGH);
    }
    Serial.println(xSpeed);
    for (int k = 0; k < 100; k++) {
      digitalWrite(xStepPin, HIGH);
      vTaskDelay(1.1 /portTICK_PERIOD_MS);
      digitalWrite(xStepPin, LOW);
      vTaskDelay(1.1 /portTICK_PERIOD_MS );  
    }
  }  
}

void TaskYStep(void *pvParameters) {
  for (;;) {
    vTaskDelay(10.0 / portTICK_PERIOD_MS);
  }  
}

void loop() {}
