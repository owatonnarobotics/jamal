// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include "math.h"
#include <frc/XboxController.h>
#include <frc/Victor.h>
#include <rev/CANSparkMax.h>
#include <cameraserver/CameraServer.h>
  

frc::XboxController Pogger1(0);
frc::Victor PepeLeft(3);
frc::Victor PepeRight(2);
frc::Victor NotButtShooter(8);
frc::Victor BaesdRatioCringedexer(5);

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);



  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  frc::CameraServer::GetInstance()->StartAutomaticCapture();
}

void Robot::RobotPeriodic() {

}

void Robot::AutonomousInit() {

  PepeLeft.Set(0.5);
  PepeRight.Set(-0.5);
  frc::Wait(3.96969420); //blame joe for this monstrosity.
  PepeLeft.Set(0);
  PepeRight.Set(0);
  frc::Wait(3);
  NotButtShooter.Set (1);
  frc::Wait(2);
  BaesdRatioCringedexer.Set(0.7);
  frc::Wait(3);
  BaesdRatioCringedexer.Set(0);
  NotButtShooter.Set (0);
  
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {

   // PepeLeft.SetInverted (true);

   NotButtShooter.Set (0);
}

void Robot::TeleopPeriodic() {


  double rightTriggerX = Pogger1.GetTriggerAxis(frc::GenericHID::kRightHand) * 0.75;
  double leftTriggerX = Pogger1.GetTriggerAxis(frc::GenericHID::kLeftHand) * 0.75;

  double speedToSet = rightTriggerX - leftTriggerX;


  PepeLeft.Set(speedToSet);
  PepeRight.Set(speedToSet);
 

  if (Pogger1.GetX(frc::GenericHID::kLeftHand) > 0) {
    PepeLeft.Set(speedToSet + Pogger1.GetX(frc::GenericHID::kLeftHand) / 2);
    PepeRight.Set(speedToSet + Pogger1.GetX(frc::GenericHID::kLeftHand) / -2);

  }

  else
  {
    PepeRight.Set(speedToSet - Pogger1.GetX(frc::GenericHID::kLeftHand) / 2);
    PepeLeft.Set(speedToSet - Pogger1.GetX(frc::GenericHID::kLeftHand) / -2);

  }


  frc::SmartDashboard::PutNumber("Trigger Test", Pogger1.GetY(frc::GenericHID::kRightHand));


  if (abs(Pogger1.GetY(frc::GenericHID::kRightHand)) < 0.1) {

    NotButtShooter.Set (0);
  }

  else { 
    NotButtShooter.Set (abs(Pogger1.GetY(frc::GenericHID::kRightHand)));
    }

  if (Pogger1.GetBumper(frc::GenericHID::kLeftHand))  {

    BaesdRatioCringedexer.Set(0.7);
  }

  else {

    BaesdRatioCringedexer.Set(0);
  }

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
