/*
  ==============================================================================

    V.h
    Created: 23 Feb 2019 6:13:19pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "OnePort.h"
#include "WDF.h"

class V : public WDF{
    
public:
    V(double,double);
    ~V();
    double WaveUp() override;
    void WaveDown(double) override;
    //void setVoltage(double);
    
private:
    
    
};
