/*
  ==============================================================================

    V.cpp
    Created: 23 Feb 2019 6:13:19pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include "V.h"
V::V(double sourveVolt, double res){
    setVoltage(sourveVolt);
    setPortRes(res);
};

V::~V(){};

double V::WaveUp(){
    double wave = 2*getVoltage()-getWD();
    setWU(wave);
    return wave;
};

void V::WaveDown(double parentWave){
    setWD(parentWave);
    };

