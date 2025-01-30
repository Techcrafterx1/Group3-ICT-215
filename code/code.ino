// Pin Definitions
#define TRIG_PIN 4
#define ECHO_PIN 5
#define MOTOR_IN1 9
#define MOTOR_IN2 10
#define BUZZER_PIN 11
#define LED_PIN 12

void setup() {
  // Motor Pins
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  // Ultrasonic Sensor Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Buzzer and LED Pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Serial Monitor for Debugging
  Serial.begin(9600);
}

void loop() {
  // Variables
  long duration, distance;

  // Ensure proper trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(15);  // Set to 15 µs for added margin
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  if (duration == 0) {
    distance = 400; // Max distance when no echo detected
  } else {
    distance = duration * 0.034 / 2;
  }

  // Debug output
  Serial.print("Distance: ");
  Serial.println(distance);

  // Obstacle detection logic
  if (distance < 20) {
    // Stop motor and sound buzzer
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    // Move forward and turn on LED
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(LED_PIN, HIGH);
  }

  delay(100);
}