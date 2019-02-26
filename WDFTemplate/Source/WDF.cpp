/*
  ==============================================================================

    WDF.cpp
    Created: 23 Feb 2019 6:14:13pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/
#include <iostream>
#include "WDF.h"

WDF::WDF(){
    PortRes = 1;
};

WDF::~WDF(){
};

double WDF::Voltage(){
    double Volts = (getWU()+getWD())/2;
    return Volts;
};

double WDF::getVoltage(){
    return E;
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
