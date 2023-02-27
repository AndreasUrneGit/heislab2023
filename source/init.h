#pragma once
#include <time.h>
#include <printf.h>

#include "driver/elevio.h"

typedef enum { 
    FSM_wait,
    FSM_move,
    FSM_doorOpen,
    FSM_stop
} FSM;

volatile int glob_ElevatorStateNormal; //0 during init, 1 else
volatile FSM glob_State;
volatile MotorDirection glob_MotorDirection; // Current direction for elevator motor
volatile MotorDirection glob_QueDirection; // 
volatile int glob_LastFloor;

volatile int elevMatrix[N_FLOORS][N_BUTTONS];

void init();