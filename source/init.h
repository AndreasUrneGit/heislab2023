#pragma once

#include "driver/elevio.h"
#include "orderHandler.h"

typedef enum { 
    FSM_wait,
    FSM_move,
    FSM_doorOpen,
    FSM_stop
} FSM;

int glob_ElevatorStateNormal; //0 during init, 1 else
FSM glob_State;
MotorDirection glob_MotorDirection; //Current direction for elvio motor
MotorDirection glob_QueDirection; //direction on elvio

void init();