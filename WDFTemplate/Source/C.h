/*
  ==============================================================================

    C.h
    Created: 23 Feb 2019 6:12:52pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "OnePort.h"
#include "WDF.h"

class C : public WDF{
    
public:
    C(double);
    ~C();
    double WaveUp() override;
    void WaveDown(double) override;
    
private:
    double State;
    
};
