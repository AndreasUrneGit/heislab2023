#pragma once
#include "driver/elevio.h"
#include "FSM.h"

int elevMatrix[N_FLOORS][N_BUTTONS] = { 0 };

void stopBtnPressed(void);
void updateMatrixAndLights(void);
void orderServed(void);
void matrix(void);
