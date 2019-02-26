/*
  ==============================================================================

    ser.cpp
    Created: 23 Feb 2019 6:13:42pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/


#include "WDF.h"
#include "memory"
#include "ser.h"
#include <iostream>

ser::ser(std::shared_ptr<WDF> left, std::shared_ptr<WDF> right)// : Adaptor(left, right)
    {
    double res = left->getPortRes()+right->getPortRes();
    setPortRes(res);
        
    LeftChild = left;
    RightChild = right;
}
ser::~ser(){
};

double ser::WaveUp(){
    double wave = -(getLeftChild()->WaveUp()+getRightChild()->WaveUp());
    setWU(wave);
    return wave;
};

void ser::WaveDown(double parentWave){
    setWD(parentWave);
    
    double WDL = getLeftChild()->getWU()-(getLeftChild()->getPortRes()/getPortRes())*(parentWave+getLeftChild()->getWU()+getRightChild()->getWU());
    
    getLeftChild()->WaveDown(WDL);
    
    double WDR = getRightChild()->getWU()-(getRightChild()->getPortRes()/getPortRes())*(parentWave+getLeftChild()->getWU()+getRightChild()->getWU());
    
    getRightChild()->WaveDown(WDR);
};

std::shared_ptr<WDF> ser::getLeftChild(){
    return LeftChild;
}

std::shared_ptr<WDF> ser::getRightChild(){
    return RightChild;
}

