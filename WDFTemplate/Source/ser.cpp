/*
  ==============================================================================

    ser.cpp
    Created: 23 Feb 2019 6:13:42pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include "ser.h"
#include "WDF.h"
#include "Adaptor.h"

ser::ser(WDF left, WDF right) : Adaptor(left, right) {
    double res = left.getPortRes()+right.getPortRes();
    setPortRes(res);
}
ser::~ser(){
};

double ser::WaveUp(){
    double wave = -(getLeftChild().WaveUp()+getRightChild().WaveUp());
    setWU(wave);
    return wave;
};

void ser::WaveDown(double parentWave){
    setWD(parentWave);
    
    double WDL = getLeftChild().getWU()-(getLeftChild().getPortRes()/getPortRes())*(parentWave+getLeftChild().getWU()+getRightChild().getWU());
    getLeftChild().WaveDown(WDL);
    
    double WDR = getRightChild().getWU()-(getRightChild().getPortRes()/getPortRes())*(parentWave+getLeftChild().getWU()+getRightChild().getWU());
    getRightChild().WaveDown(WDR);
};
