#include <Stepper.h>

// Pin definitions for ultrasonic sensor
const int triggerPin = 9;  // Ultrasonic sensor trigger pin
const int echoPin = 8;     // Ultrasonic sensor echo pin

// Constants for stepper motor
const int stepsPerRevolution = 2048;  // Number of steps per revolution for 28BYJ-48 stepper motor
int motorSpeed;                       // Variable to store motor speed

// Create a Stepper motor object with IN1, IN2, IN3, IN4 pins (connected to the ULN2003 driver)
Stepper mystepper(stepsPerRevolution, 10, 12, 11, 13);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set ultrasonic sensor pins
  pinMode(triggerPin, OUTPUT);  // Set trigger pin as output
  pinMode(echoPin, INPUT);      // Set echo pin as input

  // Set initial speed of the stepper motor
  mystepper.setSpeed(5);  // Start with the motor stopped
}

void loop() {
  // Measure the distance using the ultrasonic sensor
  long duration = getDistance();
  int distance = duration * 0.034 / 2;  // Convert duration to distance (cm)

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Determine motor speed based on the distance
  if (distance > 20) {
    motorSpeed = 1;     // Stop the motor if the distance is greater than 20 cm
  } else if (distance > 15) {
    motorSpeed = 5;     // Set motor speed to 5 RPM for distances between 15 and 20 cm
  } else if (distance > 10) {
    motorSpeed = 9;    // Set motor speed to 10 RPM for distances between 10 and 15 cm
  } else if (distance > 5) {
    motorSpeed = 15;    // Set motor speed to 15 RPM for distances between 5 and 10 cm
  }

  // Set the stepper motor speed
  mystepper.setSpeed(motorSpeed);

  // Move the stepper motor forward and backward
  if (motorSpeed > 0) {
    mystepper.step(stepsPerRevolution / 100);  // Small step for smoother operation
  }

  delay(1000);  // Small delay to avoid rapid oscillations
}

// Function to measure the distance using the ultrasonic sensor
long getDistance() {
  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the pulse duration in microseconds
  long duration = pulseIn(echoPin, HIGH);
  return duration;
}
