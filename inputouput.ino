// HC-SR04 pins
const int trigPin = 7;  // TRIG
const int echoPin = 6;  // ECHO


// Motion output to Pi
const int motionPin = 8; // D8


// Distance threshold (cm) for motion
const long threshold = 50;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motionPin, OUTPUT);
  digitalWrite(motionPin, LOW);
}


void loop() {
  long duration, distance;


  // Trigger HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  // Read echo pulse duration
  duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  // Calculate distance in cm
  distance = duration * 0.034 / 2;


  // Motion detection logic
  if (distance > 0 && distance < threshold) {
    digitalWrite(motionPin, HIGH); // motion detected
  } else {
    digitalWrite(motionPin, LOW);  // no motion
  }


  delay(100); // small delay to avoid flooding Pi
}
