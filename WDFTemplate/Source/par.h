/*
  ==============================================================================

    par.h
    Created: 23 Feb 2019 6:13:36pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "Adaptor.h"
#include "WDF.h"


class par : public WDF{
    
public:
    par(WDF*, WDF*);
    ~par();
    double WaveUp() override;
    void WaveDown(double) override;
    
    // no adaptor
    WDF* getLeftChild();
    WDF* getRightChild();
private:
    
    
    // No adaptor
    WDF* LeftChild;
    WDF* RightChild;
    
};
