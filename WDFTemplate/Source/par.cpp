/*
  ==============================================================================

    par.cpp
    Created: 23 Feb 2019 6:13:36pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include "par.h"
#include "WDF.h"
#include "Adaptor.h"

par::par(WDF left, WDF right) : Adaptor(left, right) {
    double res = left.getPortRes()+right.getPortRes();
    setPortRes(res);
}
par::~par(){
};

double par::WaveUp(){
    double wave = -(getLeftChild().WaveUp()+getRightChild().WaveUp());
    setWU(wave);
    return wave;
};

void par::WaveDown(double parentWave){
    setWD(parentWave);
   
    double G1 = 1/getPortRes();
    double A1 = getWD();
    double G2 = 1/getLeftChild().getPortRes();
    double A2 = getLeftChild().getWU();
    double G3 = 1/getRightChild().getPortRes();
    double A3 = getRightChild().getWU();
    
    double B = 2*(G1*A1+G2*A2+G3*A3)/(G1+G2+G3);
    double WDL = B-A2;
    double WDR = B-A3;
   
    getLeftChild().WaveDown(WDL);
    getRightChild().WaveDown(WDR);
};
