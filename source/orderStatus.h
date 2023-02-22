#pragma once
#include "driver/elevio.h"
#include <vector>

elevMatrix[N_FLOORS][N_BUTTONS];


updateMatrix(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
            elevMatrix[f][b] = btnPressed;
        }
    }
}