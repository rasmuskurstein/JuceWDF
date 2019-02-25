/*
  ==============================================================================

    L.cpp
    Created: 23 Feb 2019 6:13:04pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include "L.h"
L::L(double res){
    setPortRes(res);
    State = 0;
};

L::~L(){};

double L::WaveUp(){
    setWU(State);
    return State;
};

void L::WaveDown(double parentWave){
    setWD(parentWave);
    State = parentWave;
};
