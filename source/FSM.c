#include "FSM.h"

void STATE_wait(){
    while(!elevio_stopButton() && !glob_MotorDirection){
        matrix();
    }
    if(elevio_stopButton()){
        glob_State = FSM_stop;
    }
    else{
        glob_State = FSM_move;
    }
    return;
}

void STATE_move(){
    elevio_motorDirection(glob_MotorDirection);
    while(!elevio_stopButton() && glob_MotorDirection){
        matrix();
    }
    elevio_motorDirection(DIRN_STOP);
    if(elevio_stopButton()){
        glob_State = FSM_stop;
        return;
    }
    glob_State = FSM_doorOpen;
    return;
}

void STATE_doorOpen(){
    elevio_doorOpenLamp(1);
    time_t start = time(NULL);
    while(time(NULL) - start < 3 && !elevio_stopButton() && !elevio_obstruction()){
        matrix();
    }
    if(elevio_stopButton()){
        glob_State = FSM_stop;
        return;
    }
    if(elevio_obstruction()){
        return;
    }
    elevio_doorOpenLamp(0);
    glob_State = FSM_wait;
    return;
}

void STATE_stop(){
    //må vi ikke stoppe motoren her?
    elevio_stopLamp(1);
    matrix();
    if(elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
    }
    while(elevio_stopButton()){

    }
    elevio_stopLamp(0);
    time_t start = time(NULL);
    while(elevio_floorSensor() != -1 && !elevio_stopButton() && time(NULL) - start < 3){
        matrix();
    }
    elevio_doorOpenLamp(0);
    glob_State = FSM_wait;
    return;
}