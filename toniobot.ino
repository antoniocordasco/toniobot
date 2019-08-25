#include <AFMotor.h>
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal Library 
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27 , 16, 2); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
AF_Stepper Stepper1(50, 1);
AF_DCMotor motorLeft(4, MOTOR34_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motorRight(3, MOTOR34_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency


const int turnSpeed = 240;
const int forwardSpeed = 220;
const int trigPin = A2;
const int echoPin = A3;

long duration;
int distance;

void displayIntro() {
  Wire.begin();
  lcd.begin(16,2);
  delay(2000);  
  lcd.init();
  lcd.print("Toniobot ");
  delay(1000);
  lcd.print("v1.0");
  delay(2000);  
  lcd.clear();
  lcd.blink();  
  lcd.print("Mission:");
  delay(2000); 
  lcd.clear();
  lcd.blink(); 
  lcd.print("Destroy all");
  lcd.setCursor(0,1);
  lcd.print("humans");
  delay(4000); 
}

void setup() {
  
  Stepper1.setSpeed(50);
  motorLeft.setSpeed(forwardSpeed);     // set the speed to 200/255
  motorRight.setSpeed(forwardSpeed);     // set the speed to 200/255
  
  displayIntro();
  
// delay(6000000); // sleeps for 100 minutes, comment this out ot make the robot run

 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(9600); // Starts the serial communication
}

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

void loop() {  
  distance = getDistance();  
  if (distance > 30) {
    stepForward();    
  } else {
    turnWhereIsMoreSpace();    
  }
  
  delay(2000);
}
