

// runs forward for 1 second
void stepForward() {  
   motorLeft.run(FORWARD);  
   motorRight.run(FORWARD);      // turn it on going forward
   delay(500);
   motorLeft.run(RELEASE);
   motorRight.run(RELEASE);  
}

// turns left
void turnLeft() {  
   motorLeft.setSpeed(turnSpeed);
   motorRight.setSpeed(turnSpeed);
   motorLeft.run(BACKWARD);  
   motorRight.run(FORWARD);      // turn it on going forward
   delay(500);
   motorLeft.run(RELEASE);
   motorRight.run(RELEASE);  
   motorLeft.setSpeed(forwardSpeed); 
   motorRight.setSpeed(forwardSpeed);
}

// turns right
void turnRight() {
   motorLeft.setSpeed(turnSpeed);
   motorRight.setSpeed(turnSpeed);
   motorLeft.run(FORWARD);  
   motorRight.run(BACKWARD);      // turn it on going forward
   delay(500);
   motorLeft.run(RELEASE);
   motorRight.run(RELEASE); 
   motorLeft.setSpeed(forwardSpeed); 
   motorRight.setSpeed(forwardSpeed);
}

void turnWhereIsMoreSpace() {    
  Stepper1.step(8, BACKWARD, MICROSTEP);
  int distanceRight = getDistance();  
  Serial.print("Distance right: ");
  Serial.println(distanceRight);
  delay(1000);
  
  Stepper1.step(16, FORWARD, MICROSTEP);
  int distanceLeft = getDistance();  
  Serial.print("Distance left: ");
  Serial.println(distanceLeft);  
  delay(1000);
  Stepper1.step(8, BACKWARD, MICROSTEP);
  delay(1000);
  if (distanceRight > distanceLeft) {
    turnRight();
  } else {
    turnLeft();
  }
}

int getDistance() {  
  delay(100);
  long duration;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  return duration*0.034/2;
}
