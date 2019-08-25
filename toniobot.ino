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

void loop() {  
  distance = getDistance();  
  if (distance > 30) {
    stepForward();    
  } else {
    turnWhereIsMoreSpace();    
  }
  
  delay(2000);
}
