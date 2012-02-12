#ifndef ROBOTMAP_H
#define ROBOTMAP_H

//Joysticks
static const int LEFT_JOYSTICK_PORT = 1;
static const int RIGHT_JOYSTICK_PORT = 2;


//PWMs
static const int LEFT_DRIVE = 1;
static const int RIGHT_DRIVE = 2; 

static const int PASSER_MOTOR = 3;

static const int TOP_CONVEYOR_MOTOR = 5;
static const int BOTTOM_CONVEYOR_MOTOR = 6;

static const int PUNCHER_MOTOR = 7;

static const int COLLAR_MOTOR_PWM = 8;

//DIOs
static const int BOTTOM_SENSOR = 1;
static const int TOP_SENSOR = 2;
static const int SHOOTER_SENSOR = 3;

static const int PUNCHER_SENSOR = 4;

static const int TURRET_ENCODER_PORT_A = 5;
static const int TURRET_ENCODER_PORT_B = 6;

static const int COLLAR_ENCDR_ACHNL_DIN = 7;
static const int COLLAR_ENCDR_BCHNL_DIN = 8;

//Constants
static const int PUNCHER_STOP_STATE = 0;
static const int PUNCHER_START_STATE = 1;
static const int PUNCHER_RUN_STATE = 2;
static const int COLLAR_FWD_LIM_DIN = 9;
static const int COLLAR_REV_LIM_DIN = 10;

#endif
