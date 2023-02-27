#pragma once
#include "driver/elevio.h"
#include "init.h"

void stopBtnPressed(void);
void updateMatrixAndLights(void);
void orderServed(void);
void matrix(void);
void checkIfShallStop(void);
void updateDirection(void);
void printMatrix(void); //debug function to print matrix
int checkOrderUnder(void);
int checkOrderOver(void);