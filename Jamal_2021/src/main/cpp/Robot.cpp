// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include "math.h"
#include <frc/XboxController.h>
#include <frc/Victor.h>

frc::XboxController Pogger1(0);
frc::Victor PepeLeft(1);
frc::Victor PepeRight(0);

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);


  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void Robot::RobotPeriodic() {

}

void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {

    PepeLeft.SetInverted (true);
}

void Robot::TeleopPeriodic() {


  double rightTriggerX = Pogger1.GetTriggerAxis(frc::GenericHID::kRightHand) * 0.75;
  double leftTriggerX = Pogger1.GetTriggerAxis(frc::GenericHID::kLeftHand) * 0.75;

  double speedToSet = rightTriggerX - leftTriggerX;


  PepeLeft.Set(speedToSet);
  PepeRight.Set(speedToSet);
 

  if (Pogger1.GetX(frc::GenericHID::kLeftHand) > 0) {
    PepeLeft.Set(speedToSet - Pogger1.GetX(frc::GenericHID::kLeftHand));
  }

  else
  {
    PepeLeft.Set(speedToSet - Pogger1.GetX(frc::GenericHID::kLeftHand));
  }
  


  frc::SmartDashboard::PutNumber("Trigger Test" , speedToSet);


}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
