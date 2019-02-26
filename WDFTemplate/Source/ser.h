/*
  ==============================================================================

    ser.h
    Created: 23 Feb 2019 6:13:42pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "Adaptor.h"
#include "WDF.h"

class ser : public WDF{
    
public:
    ser(WDF*, WDF*);
    ~ser();
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
