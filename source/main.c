#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "FSM.h"

int main(){
    
    elevio_init(); 
    
    init(); // Get to known state

    printMatrix();

    while(1){

        switch (glob_State){

        case FSM_wait:
            STATE_wait();
            break;

        case FSM_move:
            STATE_move();
            break;

        case FSM_doorOpen:
            STATE_doorOpen();
            break;

        case FSM_stop:
            STATE_stop();
            break;
        }
    }
    return 0;
}
