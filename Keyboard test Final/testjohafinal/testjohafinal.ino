// Define pins for L298 motor driver
const int motor1Pin1 = 3;  // IN1 for Motor 1
const int motor1Pin2 = 4;  // IN2 for Motor 1
const int motor2Pin1 = 5;  // IN3 for Motor 2
const int motor2Pin2 = 6;  // IN4 for Motor 2

// Analog pins
int analogPin1 = A0;  // Analog pin 0 for the first sensor
int analogPin2 = A1;  // Analog pin 1 for the second sensor

// Variables to store analog sensor values
int sensorValue1 = 0;
int sensorValue2 = 0;

// Variables for scaled values
int scaledValue1 = 0;  // Scaled value for Signal 1
int scaledValue2 = 0;  // Scaled value for Signal 2

void setup() {
  Serial.begin(9600);  // Start serial communication to get input from the Serial Monitor
  
  // Set motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  // Read the values from the analog pins
  sensorValue1 = analogRead(analogPin1);
  sensorValue2 = analogRead(analogPin2);

  // Map the analog signal values (0-1023) to the range 1-100
  scaledValue1 = map(sensorValue1, 0, 1023, 1, 256);
  scaledValue2 = map(sensorValue2, 0, 1023, 1, 256);

  // Print the scaled values to the Serial Monitor
  Serial.print("Focus Value (Press- 1 and 2): ");
  Serial.print(scaledValue1);
  Serial.print(" | Zoom Value (Press- 3 and 4): ");
  Serial.println(scaledValue2);

  // Wait for user input from Serial Monitor
  if (Serial.available() > 0) {
    char input = Serial.read();  // Read the input from the Serial Monitor

    // Check which key was pressed and take the appropriate action
    if (input == '1') {
      // Rotate Motor 2 forward for 100ms
      Serial.println("Press '1' - Rotate Motor 2 Forward for 25ms");
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(10);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '2') {
      // Rotate Motor 2 backward for 100ms
      Serial.println("Press '2' - Rotate Motor 2 Backward for 25ms");
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(10);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '3') {
      // Rotate Motor 1 forward for 100ms
      Serial.println("Press '3' - Rotate Motor 1 Forward for 100ms");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      delay(35);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '4') {
      // Rotate Motor 1 backward for 100ms
      Serial.println("Press '4' - Rotate Motor 1 Backward for 100ms");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay(35);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '5') {
      // Rotate Motor 2 forward for 100ms
      Serial.println("Press '1' - Rotate Motor 2 Forward for 25ms");
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(10*50);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '6') {
      // Rotate Motor 2 backward for 100ms
      Serial.println("Press '2' - Rotate Motor 2 Backward for 25ms");
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(10*50);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '7') {
      // Rotate Motor 1 forward for 100ms
      Serial.println("Press '3' - Rotate Motor 1 Forward for 100ms");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      delay(10*50);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 
    else if (input == '8') {
      // Rotate Motor 1 backward for 100ms
      Serial.println("Press '4' - Rotate Motor 1 Backward for 100ms");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay(10*50);  // Rotate motor for 100ms
      stopMotors();  // Stop motors after 100ms
    } 

  }
}

void stopMotors() {
  // Stop both motors
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
