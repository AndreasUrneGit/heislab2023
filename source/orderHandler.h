#pragma once
#include "driver/elevio.h"
#include "FSM.h"

int elevMatrix[N_FLOORS][N_BUTTONS];

void stopBtnPressed(void);
void updateMatrixAndLights(void);
void orderServed(void);
void matrix(void);
void checkIfShallStop(void);
void printMatrix(void); //debug function to print matrix