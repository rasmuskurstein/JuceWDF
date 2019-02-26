/*
  ==============================================================================

    ser.h
    Created: 23 Feb 2019 6:13:42pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "WDF.h"

class ser : public WDF{
    
public:
    ser(std::shared_ptr<WDF>, std::shared_ptr<WDF>);
    ~ser();
    double WaveUp() override;
    void WaveDown(double) override;
    
    std::shared_ptr<WDF> getLeftChild();
    std::shared_ptr<WDF> getRightChild();
private:
    
    // No adaptor
    std::shared_ptr<WDF> LeftChild;
    std::shared_ptr<WDF> RightChild;
};
