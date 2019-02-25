/*
  ==============================================================================

    L.h
    Created: 23 Feb 2019 6:13:04pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "OnePort.h"
class L : public WDF{
    
public:
    L(double);
    ~L();
    double WaveUp() override;
    void WaveDown(double) override;
    
private:
    double State;
    
};
