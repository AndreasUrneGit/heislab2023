#pragma once

#include "driver/elevio.h"

typedef enum { 
    FSM_wait,
    FSM_move,
    FSM_doorOpen,
    FSM_stop
} FSM;

int glob_ElevatorStateNormal; //0 during init, 1 else
int glob_Direction; //-1 current direction down, 1 up and 0 undef
FSM glob_State;
MotorDirection glob_MotorDirection;

void init();