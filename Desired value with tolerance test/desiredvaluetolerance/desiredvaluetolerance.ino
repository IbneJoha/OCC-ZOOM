// Define pins for L298 motor driver
const int motor1Pin1 = 3, motor1Pin2 = 4;  // Motor 1
const int motor2Pin1 = 5, motor2Pin2 = 6;  // Motor 2

// Analog input pins
const int analogPin1 = A0, analogPin2 = A1;

// Desired values
const int desiredValue1 = 50;  // Desired target for motor 1
const int desiredValue2 = 50;  // Desired target for motor 2

// Tolerance for stopping
const int tolerance = 5;

// Variables to store calibration directions
int motor1Direction = 0;  // 1 for Forward, -1 for Backward
int motor2Direction = 0;  // 1 for Forward, -1 for Backward

void setup() {
  Serial.begin(9600);

  // Set motor pins as OUTPUT
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Perform calibration for motor 1
  calibrateMotor(analogPin1, motor1Pin1, motor1Pin2, motor1Direction);
  
  // Perform calibration for motor 2
  calibrateMotor(analogPin2, motor2Pin1, motor2Pin2, motor2Direction);
}

// Calibration function to check motor direction
void calibrateMotor(int analogPin, int pin1, int pin2, int &direction) {
  int initialValue = map(analogRead(analogPin), 0, 1023, 0, 100);
  Serial.print("Initial value for calibration: ");
  Serial.println(initialValue);
  
  // Move motor forward
  Serial.println("Moving motor forward...");
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  delay(2000);  // Wait for motor to move
  int valueForward = map(analogRead(analogPin), 0, 1023, 0, 100);
  Serial.print("Value after moving forward: ");
  Serial.println(valueForward);

  // Move motor backward
  Serial.println("Moving motor backward...");
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  delay(2000);  // Wait for motor to move
  int valueBackward = map(analogRead(analogPin), 0, 1023, 0, 100);
  Serial.print("Value after moving backward: ");
  Serial.println(valueBackward);

  // Determine direction based on the change in value
  if (valueBackward < valueForward) {
    Serial.println("Motor direction: Forward");
    direction = 1;  // Forward direction
  } else {
    Serial.println("Motor direction: Backward");
    direction = -1;  // Backward direction
  }

  // Stop motor after calibration
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  delay(1000);
}

// Main loop function that runs continuously
void loop() {
  // Read and scale values
  int scaledValue1 = map(analogRead(analogPin1), 0, 1023, 0, 100);
  int scaledValue2 = map(analogRead(analogPin2), 0, 1023, 0, 100);

  // Print current scaled values for debugging
  Serial.print("Scaled Value 1: "); Serial.print(scaledValue1);
  Serial.print(" | Scaled Value 2: "); Serial.println(scaledValue2);

  // Control motors using updated logic
  controlMotor(scaledValue1, desiredValue1, motor1Pin1, motor1Pin2, motor1Direction);
  controlMotor(scaledValue2, desiredValue2, motor2Pin1, motor2Pin2, motor2Direction);

  delay(500);  // Stability delay
}

// Function to control motor direction based on scaled value and desired value
void controlMotor(int currentScaledValue, int desiredValue, int pin1, int pin2, int direction) {
  // Debugging output
  Serial.print("Current Scaled Value: ");
  Serial.print(currentScaledValue);
  Serial.print(" | Desired Value: ");
  Serial.println(desiredValue);

  // If the scaled value is lower than the desired value, move forward
  if (currentScaledValue < desiredValue - tolerance) {
    Serial.println("Motor Forward to increase value.");
    if (direction == 1) {
      digitalWrite(pin1, HIGH);  // Move forward
      digitalWrite(pin2, LOW);
    } else {
      digitalWrite(pin1, LOW);   // Move backward (reverse direction)
      digitalWrite(pin2, HIGH);
    }
  } 
  // If the scaled value is higher than the desired value, move backward
  else if (currentScaledValue > desiredValue + tolerance) {
    Serial.println("Motor Backward to decrease value.");
    if (direction == -1) {
      digitalWrite(pin1, LOW);   // Move backward
      digitalWrite(pin2, HIGH);
    } else {
      digitalWrite(pin1, HIGH);  // Move forward (reverse direction)
      digitalWrite(pin2, LOW);
    }
  } 
  // If the scaled value is within tolerance, stop the motor
  else {
    Serial.println("Motor stopped at desired value.");
    digitalWrite(pin1, LOW);  // Stop the motor
    digitalWrite(pin2, LOW);
  }

  // Small delay for smoother operation
  delay(300);
}
