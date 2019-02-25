/*
  ==============================================================================

    par.h
    Created: 23 Feb 2019 6:13:36pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "Adaptor.h"

class par : public Adaptor{
    
public:
    par(WDF, WDF);
    ~par();
    double WaveUp() override;
    void WaveDown(double) override;
    
private:
    
    
};
