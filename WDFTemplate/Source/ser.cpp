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
    // DAFX (12.16)
    setWD(parentWave);
    double A1 = parentWave;
    double A2 = getLeftChild()->getWU();
    double A3 = getRightChild()->getWU();
    double R1 = getPortRes();
    double R2 = getLeftChild()->getPortRes();
    double R3 = getRightChild()->getPortRes();
    
    double WDL = A2 - 2*R2*(A1+A2+A3)/(R1+R2+R3);
    double WDR = A3 - 2*R3*(A1+A2+A3)/(R1+R2+R3);
   
    getLeftChild()->WaveDown(WDL);
    getRightChild()->WaveDown(WDR);
};

std::shared_ptr<WDF> ser::getLeftChild(){
    return LeftChild;
}

std::shared_ptr<WDF> ser::getRightChild(){
    return RightChild;
}

