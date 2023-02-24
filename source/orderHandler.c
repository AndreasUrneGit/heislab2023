#include "orderHandler.h"
#include <string.h>

//må sjekke om vi skal stoppe

void matrix(){
    //first we check for stop btn
    if (elevio_stopButton()){
        stopBtnPressed();
        return;
    }

    updateMatrixAndLights();
    if (glob_State == FSM_move && elevio_floorSensor() != -1){
        checkIfShallStop();
    }
    return;
}

//in case stop button is pressed
void stopBtnPressed(void){
    memset(elevMatrix, 0, sizeof(elevMatrix)); //clear matrix to 0
    for(int f = 0; f < N_FLOORS; f++){ //setting all lights to 0
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
    return;
}

//then we update lights and matrix
void updateMatrixAndLights(void){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed){ //only updating when button pressed
                elevio_buttonLamp(f, b, btnPressed);
                elevMatrix[f][b] = btnPressed;
            }
        }
    }

    //If transition from one to another direction it loops through all this twice. Cant loop in code in case of no que
    if(glob_State == FSM_wait){
        updateDirection();
        glob_MotorDirection = glob_QueDirection;
    }
    return;
}

void orderServed(void){
    for (int buttons = 0; buttons < N_BUTTONS; buttons++){
        elevMatrix[elevio_floorSensor()][buttons] = 0;
        elevio_buttonLamp(elevio_floorSensor(), buttons, 0);
    }
    return;
}

void updateDirection(){
    if (glob_QueDirection == DIRN_STOP){
        for (int floor = 0; floor < N_FLOORS; floor++){
            for (int button = 0; button < N_BUTTONS; button++)
            {
                if (elevMatrix[floor][button] == 1){
                    if (floor > elevio_floorSensor()){
                        glob_QueDirection = DIRN_UP;
                    }
                    else{
                        glob_QueDirection = DIRN_DOWN;
                    }
                    return;
                }
            }
        }
    }

    else if (glob_State == FSM_wait && glob_QueDirection == DIRN_UP){
        glob_QueDirection = DIRN_STOP;
        for (int f = elevio_floorSensor(); f < N_FLOORS; f++){
            for (int b = 0; b < N_BUTTONS; b++){
                if (elevMatrix[f][b] != 0){
                    glob_QueDirection = DIRN_UP;
                }
                return;
            }
        }
    }

    else if (glob_State == FSM_wait && glob_QueDirection == DIRN_DOWN){
        glob_QueDirection = DIRN_STOP;
        for (int f = elevio_floorSensor(); f >= 0; f--){
            for (int b = 0; b < N_BUTTONS; b++){
                if (elevMatrix[f][b] != 0){
                    glob_QueDirection = DIRN_DOWN;
                }
                return;
            }
        }
    }
    return;
}


// function to see if we shall pick up anybody on the floor
void checkIfShallStop(void){
    int currentFloor = elevio_floorSensor();
    if(elevMatrix[currentFloor][0]){
        glob_MotorDirection = DIRN_STOP;
        return;
    }
    else if (glob_QueDirection == 1 && elevMatrix[currentFloor][1]){
        glob_MotorDirection = DIRN_STOP;
        return;
    }
    else if (glob_QueDirection == -1 && elevMatrix[currentFloor][2]){
        glob_MotorDirection = DIRN_STOP;
        return;
    }
    return;
}

void printMatrix(void){
    for (int floor  = 0; floor < N_FLOORS; floor++){
        for (int button = 0; button < N_BUTTONS; button++){
            printf("%d", elevMatrix[floor][button]);
        }
    printf("\n");
    }
}