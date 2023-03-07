#include "FSM.h"

void STATE_wait(void){
    testStart();
    while(!elevio_stopButton() && !glob_MotorDirection){
        matrix();
    }
    if(elevio_stopButton()){
        glob_State = FSM_stop;
        testSlutt();
        return;
    }
    if (glob_State != FSM_doorOpen){
        glob_State = FSM_move;
    }
    testSlutt();
    return;
}

void STATE_move(void){
    testStart();
    elevio_motorDirection(glob_MotorDirection);
    while(!elevio_stopButton() && glob_MotorDirection){
        matrix();
    }
    glob_MotorDirection = DIRN_STOP;
    elevio_motorDirection(glob_MotorDirection);
    if(elevio_stopButton()){
        glob_State = FSM_stop;
        testSlutt();
        return;
    }
    glob_State = FSM_doorOpen;
    testSlutt();
    return;
}

void STATE_doorOpen(void){
    testStart();
    elevio_doorOpenLamp(1);
    orderServed();
    time_t start = time(NULL);
    while((time(NULL) - start < 3) && !elevio_stopButton() && !elevio_obstruction()){
        matrix();
    }
    if(elevio_stopButton()){
        glob_State = FSM_stop;
        testSlutt();
        return;
    }
    if(elevio_obstruction()){
        matrix();
        testSlutt();
        return;
    }
    elevio_doorOpenLamp(0);
    glob_State = FSM_wait;
    testSlutt();
    return;
}

void STATE_stop(void){
    testStart();
    elevio_stopLamp(1);
    matrix();
    if(elevio_floorSensor() != -1){
        elevio_doorOpenLamp(1);
    }
    while(elevio_stopButton()){

    }
    elevio_stopLamp(0);

    if(elevio_floorSensor() != -1){
        testSlutt();
        glob_State = FSM_doorOpen;
        return;
    }

    elevio_doorOpenLamp(0);
    testSlutt();
    glob_State = FSM_wait;
    return;
}

void testStart(void){
    printf("Går inn i tilstand: %d ", glob_State);
    printf("\n");
    printMatrix();
}

void testSlutt(void){
    printf("\n");
    printf("Går ut av tilstand: %d", glob_State);
    printf("\n");
    printMatrix();
}