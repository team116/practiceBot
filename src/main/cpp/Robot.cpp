/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <ctre/Phoenix.h>
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>

/**
 * This is a demo program showing how to use Mecanum control with the
 * MecanumDrive class.
 */
class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override {}

  void TeleopPeriodic() override {
    double tempX, tempY, tempRotate;
    double x, y, rotate;

    // Read the Xbox Controller inputs
    tempX = -(xbox0.GetX(
        frc::GenericHID::JoystickHand::kRightHand));  // XBox Righthand joystick
    tempY = (xbox0.GetY(
        frc::GenericHID::JoystickHand::kRightHand));  // XBox Righthand Joystick
    tempRotate = -(xbox0.GetX(
        frc::GenericHID::JoystickHand::kLeftHand));  // XBox Lefthand  joystick
    // Cube them to shape the curve while maintaining the sign
    x = tempX * tempX * tempX;                      // pow(tempX,3);
    y = tempY * tempY * tempY;                      // pow(tempY,3);
    rotate = tempRotate * tempRotate * tempRotate;  // pow(tempRotate,3)

    /* Use the joystick X axis for lateral movement, Y axis for forward
     * movement, and Z axis for rotation.
     */
    m_robotDrive.DriveCartesian(tempX, tempY, rotate);
  }

 private:
  const int kJoystickChannel = 0;
  const int kFrontLeftChannel = 1;
  const int kRearLeftChannel = 2;
  const int kFrontRightChannel = 3;
  const int kRearRightChannel = 4;

  WPI_TalonSRX *m_FrontLeft = new WPI_TalonSRX(kFrontLeftChannel);
  WPI_TalonSRX *m_RearLeft = new WPI_TalonSRX(kRearLeftChannel);
  WPI_TalonSRX *m_FrontRight = new WPI_TalonSRX(kFrontRightChannel);
  WPI_TalonSRX *m_RearRight = new WPI_TalonSRX(kRearRightChannel);

  frc::MecanumDrive m_robotDrive{*m_FrontLeft, *m_RearLeft, *m_FrontRight,
                                 *m_RearRight};

  frc::XboxController xbox0{kJoystickChannel};
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
