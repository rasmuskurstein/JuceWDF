/*
  ==============================================================================

    WDF.cpp
    Created: 23 Feb 2019 6:14:13pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#include "WDF.h"

WDF::WDF(){
    PortRes = 1;
    //setWU(0);
    //setWD(0);
};

WDF::~WDF(){
};

double WDF::getVoltage(){
    float Volts = (getWU()+getWD())/2;
    return Volts;
};

void WDF::setVoltage(double volts){
    E = volts;
};

double WDF::getWU(){
    return WU;
};
double WDF::getWD(){
    return WD;
};
double WDF::getPortRes(){
    return PortRes;
};

void WDF::setWU(double wave){
    WU = wave;
};
void WDF::setWD(double wave){
    WD = wave;
};
void WDF::setPortRes(double res){
    PortRes = res;
};

double WDF::WaveUp(){
    double wave = 0;
    setWU(wave); // always zero for linear resistor
    return wave;
};

void WDF::WaveDown(double parentWave){
    setWD(parentWave);
};
