// Define pins for L298 motor driver
const int motor1Pin1 = 3, motor1Pin2 = 4;  // Motor 1
const int motor2Pin1 = 5, motor2Pin2 = 6;  // Motor 2

// Analog input pins
const int analogPin1 = A0, analogPin2 = A1;

// Desired values
const int desiredValue1 = 10;
const int desiredValue2 = 50;

// Initial scaled values for calibration
int initialScaledValue1 = 0;
int initialScaledValue2 = 0;

// Calibration flag
bool calibrated = false;

// Tolerance for stopping
const int tolerance = 5;

void setup() {
  Serial.begin(9600);

  // Set motor pins as OUTPUT
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Start calibration process
  calibrateMotor();
}

void calibrateMotor() {
  // Step 1: Read the initial scaled values
  initialScaledValue1 = map(analogRead(analogPin1), 0, 1023, 0, 100);
  initialScaledValue2 = map(analogRead(analogPin2), 0, 1023, 0, 100);
  
  Serial.println("Starting calibration...");
  Serial.print("Initial Scaled Value 1: ");
  Serial.println(initialScaledValue1);
  Serial.print("Initial Scaled Value 2: ");
  Serial.println(initialScaledValue2);
  
  // Step 2: Move motor 1 forward and read scaled value
  Serial.println("Moving Motor 1 Forward...");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);  // Allow motor to rotate for a moment
  
  int forwardValue1 = map(analogRead(analogPin1), 0, 1023, 0, 100);
  Serial.print("Scaled Value 1 after moving forward: ");
  Serial.println(forwardValue1);
  
  // Step 3: Move motor 1 backward and read scaled value
  Serial.println("Moving Motor 1 Backward...");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  delay(1000);  // Allow motor to rotate for a moment
  
  int backwardValue1 = map(analogRead(analogPin1), 0, 1023, 0, 100);
  Serial.print("Scaled Value 1 after moving backward: ");
  Serial.println(backwardValue1);
  
  // Step 4: Determine direction of movement for motor 1
  if (forwardValue1 > initialScaledValue1) {
    Serial.println("Motor 1 moves forward to increase scaled value.");
  } else if (backwardValue1 < initialScaledValue1) {
    Serial.println("Motor 1 moves backward to decrease scaled value.");
  }
  
  // Step 5: Repeat the same for motor 2
  Serial.println("Moving Motor 2 Forward...");
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);  // Allow motor to rotate for a moment
  
  int forwardValue2 = map(analogRead(analogPin2), 0, 1023, 0, 100);
  Serial.print("Scaled Value 2 after moving forward: ");
  Serial.println(forwardValue2);
  
  Serial.println("Moving Motor 2 Backward...");
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  delay(1000);  // Allow motor to rotate for a moment
  
  int backwardValue2 = map(analogRead(analogPin2), 0, 1023, 0, 100);
  Serial.print("Scaled Value 2 after moving backward: ");
  Serial.println(backwardValue2);
  
  if (forwardValue2 > initialScaledValue2) {
    Serial.println("Motor 2 moves forward to increase scaled value.");
  } else if (backwardValue2 < initialScaledValue2) {
    Serial.println("Motor 2 moves backward to decrease scaled value.");
  }
  
  // Once calibration is done, set flag
  calibrated = true;
  Serial.println("Calibration Complete.");
}

void loop() {
  // Only proceed with motor control if calibration is done
  if (!calibrated) {
    return;  // Wait for calibration
  }

  // Read and scale values
  int scaledValue1 = map(analogRead(analogPin1), 0, 1023, 0, 100);
  int scaledValue2 = map(analogRead(analogPin2), 0, 1023, 0, 100);

  // Print current scaled values
  Serial.print("Scaled Value 1: "); Serial.print(scaledValue1);
  Serial.print(" | Scaled Value 2: "); Serial.println(scaledValue2);

  // Control motors using updated calibration values
  controlMotor(scaledValue1, desiredValue1, motor1Pin1, motor1Pin2);
  controlMotor(scaledValue2, desiredValue2, motor2Pin1, motor2Pin2);

  delay(500);  // Stability delay
}

// Function to control motor direction based on scaled value and desired value
void controlMotor(int currentScaledValue, int desiredValue, int pin1, int pin2) {
  // Check if the motor needs to move
  if (currentScaledValue < desiredValue - tolerance) {
    Serial.println("Motor Forward to increase value.");
    digitalWrite(pin1, HIGH);  // Move forward
    digitalWrite(pin2, LOW);
  } else if (currentScaledValue > desiredValue + tolerance) {
    Serial.println("Motor Backward to decrease value.");
    digitalWrite(pin1, LOW);  // Move backward
    digitalWrite(pin2, HIGH);
  } else {
    Serial.println("Motor stopped at desired value.");
    digitalWrite(pin1, LOW);  // Stop the motor
    digitalWrite(pin2, LOW);
  }
}
