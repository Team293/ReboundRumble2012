#ifndef ROBOTMAP_H
#define ROBOTMAP_H

//Joysticks
static const int LEFT_JOYSTICK_PORT = 1;
static const int RIGHT_JOYSTICK_PORT = 2;
static const int GAMEPAD_PORT = 3;

static const int PUNCHER_BUTTON = 4;

//PWMs
static const int LEFT_DRIVE = 1;
static const int RIGHT_DRIVE = 2;

static const int TOP_CONVEYOR_MOTOR = 5;
static const int BOTTOM_CONVEYOR_MOTOR = 6;

static const int PUNCHER_MOTOR = 7;

static const int COLLAR_MOTOR_PWM = 8;

static const int TURRET_MOTOR_PWM = 4;

//DIOs
static const int BOTTOM_SENSOR = 10; 
static const int TOP_SENSOR = 11;
static const int SHOOTER_SENSOR = 12;

static const int PUNCHER_SENSOR = 9;

static const int COLLAR_FWD_LIM_DIN = 7;
static const int COLLAR_REV_LIM_DIN = 8;

static const int TURRET_FWD_LIM_DIN = 3;
static const int TURRET_REV_LIM_DIN = 4;

//Encoders
static const int TURRET_ENCDR_ACHNL_DIN = 1;
static const int TURRET_ENCDR_BCHNL_DIN = 2;

static const int COLLAR_ENCDR_ACHNL_DIN = 5;
static const int COLLAR_ENCDR_BCHNL_DIN = 6;

#endif
