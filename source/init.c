#include "init.h"

void init(){
    glob_ElevatorStateNormal = 0;
    glob_MotorDirection = DIRN_DOWN;
    elevio_floorIndicator(0); // We don´t want floor indication before known state
    elevio_doorOpenLamp(0); // Simulates closing of door
    elevio_motorDirection(glob_MotorDirection);
    while(elevio_floorSensor() == -1){

    }
    glob_MotorDirection = DIRN_STOP;
    elevio_motorDirection(glob_MotorDirection);
    glob_State = FSM_wait;
    glob_ElevatorStateNormal = 1;
    return;
}