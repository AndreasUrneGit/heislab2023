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

int glob_ElevatorStateNormal; //0 during init, 1 else
FSM glob_State;
MotorDirection glob_MotorDirection; // Current direction for elevator motor
MotorDirection glob_QueDirection; // 

int elevMatrix[N_FLOORS][N_BUTTONS];

void init();