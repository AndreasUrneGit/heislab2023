#include "orderHandler.h"
#include <string.h>


void matrix(){
    //first we check for stop btn
    if (elevio_stopButton()){
        stopBtnPressed();
        return;
    }

    updateMatrixAndLights();
}

//in case Stopp button is pressed
void stopBtnPressed(void){
    glob_State = FSM_stop;
    memset(elevMatrix, 0, sizeof(elevMatrix)); //clear matrix to 0
    for(int f = 0; f < N_FLOORS; f++){ //setting all lights to 0
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, 0);
        }
    }
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
    if(glob_State == FSM_wait){
        updateDirection();
    }
}

void orderServed(void){
    for (int buttons = 0; buttons < N_BUTTONS; buttons++){
        elevMatrix[elevio_floorSensor()][buttons] = 0;
        elevio_buttonLamp(elevio_floorSensor(), buttons, 0);
    }
}

void updateDirection(){

    if (glob_MotorDirection == DIRN_STOP){
        for (int floor = 0; floor < N_FLOORS; floor++){
            for (int button = 0; button < N_BUTTONS; button++)
            {
                if (elevMatrix[floor][button] == 1){
                    if (floor > elevio_floorSensor()){
                        glob_MotorDirection = DIRN_UP;
                    }
                    else{
                        glob_MotorDirection = DIRN_DOWN;
                    }
                }
            }
        }
    }

    else if (glob_State == STATE_wait && glob_MotorDirection == DIRN_UP){
        glob_MotorDirection = DIRN_STOP;
        for (int f = elevio_floorSensor(); f < N_FLOORS; f++){
            for (int b = 0; b < N_BUTTONS; b++){
                if (elevMatrix[f][b] != 0){
                    glob_MotorDirection = DIRN_UP;
                }
            }
            
            }
    }

    else if (glob_State == STATE_wait && glob_MotorDirection == DIRN_DOWN){
        glob_MotorDirection = DIRN_STOP;
        for (int f = elevio_floorSensor(); f >= 0; f--){
            for (int b = 0; b < N_BUTTONS; b++){
                if (elevMatrix[f][b] != 0){
                    glob_MotorDirection = DIRN_DOWN;
                }
            }
        }
    }
}