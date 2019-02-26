/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

 ===============================*===============================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WDF.h"
#include "V.h"
#include "R.h"
#include "C.h"
#include "L.h"
#include "par.h"
#include "ser.h"

//==============================================================================
/**
*/
class WdftemplateAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    WdftemplateAudioProcessor();
    ~WdftemplateAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    
private:
    
    double fc;       // Cutoff Freq
    double df;       // Dampening Factor
    double wc;
    
    C C1{1};
    L L1{1};
    R Vout{1};
    V Vin{0,1};
    std::shared_ptr<par> p1;
    std::shared_ptr<ser> s1;
    std::shared_ptr<ser> circuit;
    
    std::shared_ptr<L> L1Ptr = std::make_shared<L>(L1);
    std::shared_ptr<R> VoutPtr = std::make_shared<R>(Vout);
    std::shared_ptr<V> VinPtr = std::make_shared<V>(Vin);
    std::shared_ptr<C> C1Ptr = std::make_shared<C>(C1);
    
//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WdftemplateAudioProcessor)
};
