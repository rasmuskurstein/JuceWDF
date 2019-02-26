/*
  ==============================================================================

    par.h
    Created: 23 Feb 2019 6:13:36pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once
#include "WDF.h"


class par : public WDF{
    
public:
    par(std::shared_ptr<WDF>, std::shared_ptr<WDF>);
    ~par();
    double WaveUp() override;
    void WaveDown(double) override;
    
    std::shared_ptr<WDF> getLeftChild();
    std::shared_ptr<WDF> getRightChild();
private:
    
    std::shared_ptr<WDF> LeftChild;
    std::shared_ptr<WDF> RightChild;
    
};
