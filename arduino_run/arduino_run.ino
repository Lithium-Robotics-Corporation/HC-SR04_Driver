const int trig = 9;
const int echo = 10;

float duration, distance;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
}
/*
 * Gets distance from HC-SR04 sensor in centimeters. Returns a float.
 */
float getDistance() {
  //Send signal to HC-SR04 to trigger sonic burst emission
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);

  //Pulse in sonic response from the HC-SR04
  duration = pulseIn(echo, 1);
  //Time * speed = distance. Divide by 2 because the sound goes to and from object.
  distance = (duration*0.0343)/2;
  return distance;
}

//Number of values to average from the sensor
unsigned int iterations = 10;
//In microseconds
unsigned int iteration_delay = 2;

void loop() {
  //Burst fire sensor to get multiple values for distance over a short interval. This will help smooth the values received because the sensor response can jump around a bit.
  float average = 0.0;
  for(int i=0;i<iterations;i++) {
    average+=getDistance();
    delayMicroseconds(iteration_delay);
  }
  average/=iterations;
  
  Serial.print("Distance: ");
  Serial.print(average);
  Serial.println("cm");
  delay(500);
}
