/*
  ==============================================================================

    Adaptor.h
    Created: 23 Feb 2019 6:12:20pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "WDF.h"

class Adaptor : public WDF{
    
public:
    Adaptor(WDF,WDF);
    virtual ~Adaptor();
    WDF getLeftChild();
    WDF getRightChild();
   // virtual double WaveUp() override;
   // virtual void WaveDown(double) override;
    
private:
    WDF* LeftChild;
    WDF* RightChild;
};
