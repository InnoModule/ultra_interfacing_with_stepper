#include <Stepper.h>

int motorspeed = 15;
Stepper mystepper(2048, 10, 12, 11, 13);  // Corrected name for the stepper object

void setup() {
  // put your setup code here, to run once:
  mystepper.setSpeed(motorspeed);  // Use the corrected stepper object name
}

void loop() {
  // put your main code here, to run repeatedly:
  mystepper.step(2048);  // Move the stepper forward
  delay(1000);           // Wait for 1 second
  mystepper.step(-1024); // Move the stepper backward
  delay(1000);           // Wait for 1 second
}



