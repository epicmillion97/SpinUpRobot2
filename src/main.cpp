/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       epicmillion97                                             */
/*    Created:      Wed Jan 18 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FrontLeft            motor         1               
// FrontRight           motor         2               
// BackLeft             motor         3               
// BackRight            motor         4               
// Controller1          controller                    
// ColorRoller          motor         5               
// Flywheel             motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"

using namespace vex;

competition Competition;


// VARIABLES
float MaxRotationSpeed = .55; // Normal Steering Speed no Turbo
float MaxTranslationSpeed = 1; // Normal Driving Speed no Turbo
float TurboRotationSpeed = .85; // Turbo Rotation Speed 
float TurboTranslationSpeed = 1; // Turbo Translation Speed
float currentMaxRotationSpeed = MaxRotationSpeed;
float currentMaxTranslationSpeed = MaxTranslationSpeed;

float flywheelStrength = 100;




float wheelDiameter = 3.5;
float wheelCircumference = wheelDiameter * 3.141; //inches
float turningDiameter = 22;

float tile = 24;
float translationSpeed = 75;
float turningSpeed = 50;


float cap(float inputVal, float maxMinVal) { // Cap allow full use of motor range with steering
  if (inputVal > maxMinVal){
    return maxMinVal;
  } else if (inputVal < -maxMinVal) {
    return -maxMinVal;
  } else{
    return inputVal;
  };
  // if inputVal is greater than max min val, return max min val
  // if less than min val then return -maxMinVal
  // else return inputVal
}

void driveForward(float inches, float speed) {
    float inchesPerDegree = wheelCircumference / 360;
    float degrees = inches / inchesPerDegree;

    FrontRight.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    FrontLeft.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    BackRight.startRotateFor(degrees, deg, speed, vex::velocityUnits::pct);
    BackLeft.rotateFor(degrees, deg, speed, vex::velocityUnits::pct);
}


void autonomouscodenon(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.print("Autonomous");

}

void autonomouscode(){
  Controller1.Screen.clearScreen();
  Controller1.Screen.print("Autonomous");
  
}







void driverControl(){
  Controller1.Screen.clearScreen();
  while (true){
  //THE MOVE PLACE
  float V = Controller1.Axis3.position(percent); // Forward and backwards
  //float H = Controller1.Axis4.position(percent); // Strafe
  float S = Controller1.Axis1.position(percent); // Steering
    
  float vA = V * currentMaxTranslationSpeed; // Limit Forward/Backwards Speed
  //float hA = H * currentMaxTranslationSpeed; // Limit Strafe Speed
  float sA = S * currentMaxRotationSpeed; // Limit Steering Speed

  float drivetrainMax = 100 - fabsf(sA); // Max motor movement given steering is constant

  // Set Motor Velocity with Steering Prioritized with 
  float FL_motor_command = sA + cap(vA, drivetrainMax);
  float BL_motor_command = sA + cap(vA, drivetrainMax);
  float FR_motor_command = -sA + cap(vA, drivetrainMax);
  float BR_motor_command = -sA + cap(vA, drivetrainMax);
  //if (autonoumousActive == false && visionDrivingActive == false){
  // Assign Proper Velocity for Each Motor
  FrontLeft.setVelocity(FL_motor_command, percent);
  BackLeft.setVelocity(BL_motor_command, percent);
  FrontRight.setVelocity(FR_motor_command, percent);
  BackRight.setVelocity(BR_motor_command, percent);
  // Start Motors
  FrontLeft.spin(forward);
  FrontRight.spin(forward);
  BackLeft.spin(forward);
  BackRight.spin(forward);
  //}

  if(Controller1.ButtonY.pressing() == true){
    ColorRoller.setVelocity(65, percent);
    ColorRoller.spin(forward);
  } else if(Controller1.ButtonX.pressing() == true){
    ColorRoller.setVelocity(-65, percent);
    ColorRoller.spin(forward);
  } else{
    ColorRoller.setVelocity(0, percent);
  }

  if(Controller1.ButtonR2.pressing() == true) { //This is for the Flywheel
    Flywheel.setVelocity(flywheelStrength, percent); // Set Velocity of Flywheel to 100%
    Flywheel.spin(forward); // Start Motor
  } else {
    Flywheel.setVelocity(0,percent); // Stop Motor Velocity
  }

  if(Controller1.ButtonLeft.pressing() == true){ //Decreases flywheel strength
    if(flywheelStrength > 10){
      flywheelStrength-=10;
      Controller1.Screen.clearLine(2);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(flywheelStrength);
    }
    wait(400,msec);
  } else if(Controller1.ButtonRight.pressing() == true){ //Increases flywheel strength
    if(flywheelStrength < 100){
      flywheelStrength+=10;
      Controller1.Screen.clearLine(2);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print(flywheelStrength);
    }
    wait(400,msec);
  }

  wait(25,msec);
  }
}





int main() {
  Brain.Screen.clearScreen();
  Controller1.Screen.clearScreen();

  Competition.bStopAllTasksBetweenModes = true; // maybe necessary?
  Competition.autonomous(autonomouscode);
  Competition.drivercontrol(driverControl);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
