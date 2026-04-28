#include <Servo.h>

// Servo
Servo myServo;
const int servoPin = 9;

// Ultraschallsensor
const int trigPin = 10;
const int echoPin = 11;

// Motortreiber (2 Motoren)
const int motor1A = 2;
const int motor1B = 3;
const int motor2A = 4;
const int motor2B = 5;

// Hupe und Licht
const int buzzerPin = 6;
const int lightPin = 7;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  // Servo
  myServo.attach(servoPin);
  myServo.write(90); // Mitte

  // Ultraschall
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motoren
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // Hupe und Licht
  pinMode(buzzerPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
}

void loop() {
  distance = getDistance();
  Serial.println(distance);

  if (distance > 20) {
    forward();
    digitalWrite(buzzerPin, LOW);
    digitalWrite(lightPin, LOW);
  } else {
    stopMotors();
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(lightPin, HIGH);

    // Servo schaut links
    myServo.write(0);
    delay(500);

    // Servo schaut rechts
    myServo.write(180);
    delay(500);

    // Servo zurück Mitte
    myServo.write(90);
    delay(500);

    digitalWrite(buzzerPin, LOW);
    digitalWrite(lightPin, LOW);

    backward();
    delay(1000);

    stopMotors();
    delay(500);
  }

  delay(100);
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

void forward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void backward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void stopMotors() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}