/*
  ==============================================================================

    R.h
    Created: 23 Feb 2019 6:13:14pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "WDF.h"

class R : public WDF{
public:
    R(double);
    ~R();
    double WaveUp() override;
    void WaveDown(double) override;
    
private:
    
    
};
