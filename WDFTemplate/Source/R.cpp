/*
  ==============================================================================

    R.cpp
    Created: 23 Feb 2019 6:13:14pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include "R.h"
#include "WDF.h"
#include <iostream>

R::R(double res){
    setPortRes(res);
};

R::~R(){};

double R::WaveUp(){
    setWU(0); // always zero for linear resistor
    return 0;
};

void R::WaveDown(double parentWave){
    setWD(parentWave);
};
