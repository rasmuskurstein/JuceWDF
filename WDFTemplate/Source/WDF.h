/*
  ==============================================================================

    WDF.h
    Created: 23 Feb 2019 6:14:13pm
    Author:  Rasmus Kürstein

  ==============================================================================
*/

#pragma once

class WDF {
  
public:
    
    WDF();
     
    virtual ~WDF();
    
    virtual double waveUp();
    
    double getVoltage();
    void setVoltage(double);
    double getWU();
    double getWD();
    double getPortRes();
    void setWU(double);
    void setWD(double);
    void setPortRes(double);
    virtual double WaveUp();
    virtual void WaveDown(double);
    
    
private:
    double PortRes;
    double WU;
    double WD;
    double E;
};


