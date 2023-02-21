#pragma once
#include "driver/elevio.h"

int glob_ElevatorStateNormal; //0 under init, 1 eles
int glob_CurrentFloor; //current floor state
int glob_StopButton; //1 if StopButton pressed
int glob_Direction; //-1 current direction down, 1 up and 0 undef
enum FSM glob_State;
MotorDirection glob_MotorDirection;

enum FSM {FSM_wait,
        FSM_move,
        FSM_doorOpen,
        FSM_stop,
                };



void wait();
void move();
void doorOpen();
void stop();