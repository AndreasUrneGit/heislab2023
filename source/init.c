#include "init.h"

void init(){
    glob_ElevatorStateNormal = 0;
    glob_MotorDirection = DIRN_DOWN;

    for(int floor = 0; floor < N_FLOORS; floor++){ // Initialization of matrix and turning off all lights
        for(int button = 0; button < N_BUTTONS; button++){
            elevMatrix[floor][button] = 0;
            elevio_buttonLamp(floor, button, 0);
        }
    }

    elevio_doorOpenLamp(0); // Simulates closing of door
    time_t start = time(NULL);
    while(time(NULL) - start < 3){ // Wait for door to close

    }

    elevio_motorDirection(glob_MotorDirection);
    while(elevio_floorSensor() == -1){

    }

    glob_MotorDirection = DIRN_STOP;
    elevio_motorDirection(glob_MotorDirection);
    elevio_floorIndicator(elevio_floorSensor()); // Set correct floor light
    glob_State = FSM_wait;
    glob_QueDirection = DIRN_STOP;
    glob_ElevatorStateNormal = 1; // Init complete :)
    return;
}