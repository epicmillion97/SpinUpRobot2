/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       hwalden55275                                              */
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
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"

using namespace vex;

// VARIABLES
float MaxRotationSpeed = .55; // Normal Steering Speed no Turbo
float MaxTranslationSpeed = 1; // Normal Driving Speed no Turbo
float TurboRotationSpeed = .85; // Turbo Rotation Speed 
float TurboTranslationSpeed = 1; // Turbo Translation Speed
float currentMaxRotationSpeed = MaxRotationSpeed;
float currentMaxTranslationSpeed = MaxTranslationSpeed;

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


int driveTrainLoop(){ // Controls Drivetrain > Gets Joystick Position & Sets to Motors
  while(69 == 69){
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

  wait(25,msec);
  }
  return 0;
}



int main() {
  task driveTrainLoopTask = task(driveTrainLoop); // Task for drive train
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}
