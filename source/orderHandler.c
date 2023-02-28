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
    //update of elevator direction after orders are served
    if(glob_State == FSM_wait){
        updateDirection();
        glob_MotorDirection = glob_QueDirection;
    }

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
            if((f == 0 && b == 1) || (f == (N_FLOORS-1) && b == 0)){
                continue;
            }
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed){ //only updating when button pressed
                elevio_buttonLamp(f, b, btnPressed);
                elevMatrix[f][b] = btnPressed;
            }
        }
    }
    //assumption that elevio_floorIndicator takes argument of only the floor indicator to light up and doesnt need to set last used floor light to 0
    int currentFloor = elevio_floorSensor();
    if(currentFloor != -1){
        glob_LastFloor = currentFloor;
        elevio_floorIndicator(currentFloor);
    }
    return;
}

void updateDirection(){
    if (glob_QueDirection == DIRN_UP && !checkOrderOver()){
        glob_QueDirection = DIRN_STOP;
    }
    else if (glob_QueDirection == DIRN_DOWN && !checkOrderUnder()){
        glob_QueDirection = DIRN_STOP;
    }
    if (glob_QueDirection == DIRN_STOP){
        for (int floor = 0; floor < N_FLOORS; floor++){
            for (int button = 0; button < N_BUTTONS; button++){
                if (elevMatrix[floor][button] == 1){
                    if (floor > glob_LastFloor){
                        glob_QueDirection = DIRN_UP;
                    }
                    else if (floor < glob_LastFloor){
                        glob_QueDirection = DIRN_DOWN;
                    }
                    return;
                }
            }
        }
    }
    return;
}
int checkOrderUnder(void){
    for (int f = 0; f < glob_LastFloor; f++){
        for (int b = 0; b < N_BUTTONS; b++){
            if(elevMatrix[f][b] == 1){
                return 1;
            }
        }
    }
    return 0;
}

int checkOrderOver(void){
    for (int f = glob_LastFloor+1; f < N_FLOORS; f++){
        for (int b = 0; b < N_BUTTONS; b++){
            if(elevMatrix[f][b] == 1){
                return 1;
            }
        }
    }
    return 0;
}

void checkIfShallStop(void){
    int currentFloor = elevio_floorSensor();
    if(elevMatrix[currentFloor][2]){
        glob_MotorDirection = DIRN_STOP;
        return;
    }
    //last or argument is ment to catch when a pri order wishes to go oposit direction of current direction
    else if ((glob_QueDirection == 1 && elevMatrix[currentFloor][0]) || !checkOrderOver()){
        glob_MotorDirection = DIRN_STOP;
        return;
    }
    else if ((glob_QueDirection == -1 && elevMatrix[currentFloor][1]) || !checkOrderUnder()){
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

void orderServed(void){
    for (int buttons = 0; buttons < N_BUTTONS; buttons++){
        elevMatrix[elevio_floorSensor()][buttons] = 0;
        elevio_buttonLamp(elevio_floorSensor(), buttons, 0);
    }
    return;
}