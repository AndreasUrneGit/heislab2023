#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#include "FSM.h"
#include "init.h"

int main(){
    
    elevio_init(); 
    
    init(); // Get to known state

    while(1){

        switch (glob_State){

        case FSM_wait:
            STATE_wait();

        case FSM_move:
            STATE_move();

        case FSM_doorOpen:
            STATE_doorOpen();

        case FSM_stop:
            STATE_stop();
        }
    }
    return 0;
}
