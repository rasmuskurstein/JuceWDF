/*
  ==============================================================================

    C.cpp
    Created: 23 Feb 2019 6:12:52pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include <iostream>

#include "C.h"
#include "WDF.h"

C::C(double res){
    setPortRes(res);
    State = 0;
};

C::~C(){};

double C::WaveUp(){
    setWU(State);
    return State;
};

void C::WaveDown(double parentWave){
    setWD(parentWave);
    State = parentWave;
};
