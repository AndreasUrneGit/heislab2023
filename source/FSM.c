#include "FSM.h"
#include "globalVariables.h"

void wait(){
    while(!elevio_stopButton() && !glob_MotorDirection){
        matrix();
    }
    if(elevio_stopButton){
        glob_State = FSM_stop;
    }
    else{
        glob_State = FSM_move;
    }
    return;
}

void move(){
    elevio_motorDirection(glob_MotorDirection);
    while(!elevio_stopButton()){
        if(matrix()){
            break;
        }
    }
    elevio_motorDirection(DIRN_STOP);
    if(elevio_stopButton){
        glob_State = FSM_stop;
    }
    else{
        glob_State = FSM_doorOpen;
    }
    return;
}

void doorOpen(){
    while(1){
        //
        matrix();
    }
    glob_State = FSM_wait;
    return;
}

void stop(){
    elevio_stopLamp(1);
    matrix();
    if(elevio_floorSensor() != -1){
        stopDoorOpen();
    }
    while(elevio_stopButton()){

    }
    elevio_stopLamp(0);
    stopDoorClose();
    glob_State = FSM_wait;
    return;
}