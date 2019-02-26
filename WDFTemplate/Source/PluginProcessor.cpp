/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ser.h"
#include "par.h"
#include "V.h"
#include "R.h"
#include "L.h"
#include "C.h"
#include "WDF.h"



//==============================================================================
WdftemplateAudioProcessor::WdftemplateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(mpCutoff = new AudioParameterFloat ("mpCutoff", "Cutoff", 20.f, 20000.f, 10000.f));
    addParameter(mpDamp = new AudioParameterFloat ("mpDamp", "Damp", 0.f, 2.f, 0.3f));
}

WdftemplateAudioProcessor::~WdftemplateAudioProcessor()
{
}

//==============================================================================
const String WdftemplateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WdftemplateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WdftemplateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WdftemplateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WdftemplateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WdftemplateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WdftemplateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WdftemplateAudioProcessor::setCurrentProgram (int index)
{
}

const String WdftemplateAudioProcessor::getProgramName (int index)
{
    return {};
}

void WdftemplateAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WdftemplateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    fs = sampleRate;
    
    // Cutoff Freq
    fc = 100;
    wc = 2*double_Pi*fc;
    
    // Dampening Factor
    df = 0.3;
    
    //setup values for one port elements
    C1val = 3.5e-5;
    C1Ptr->setPortRes(1/(2*C1val*fs));
    L1val = square(1/wc)/C1val;
    L1Ptr->setPortRes(2*fs*L1val);
    R1val = 1/(2*df)*sqrt(L1val/C1val);
    VoutPtr->setPortRes(R1val);
    
    //connect one port elements with adaptors
    p1 = std::make_shared<par>(C1Ptr,VoutPtr);
    s1 = std::make_shared<ser>(VinPtr,p1);
    circuit = std::make_shared<ser>(s1,L1Ptr);
}

void WdftemplateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WdftemplateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WdftemplateAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    setParameters(mpCutoff->get(),mpDamp->get());
    //setDamp (mpDamp->get());
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        if (channel == 0)
        {
            for (int j = 0; j < buffer.getNumSamples(); ++j)
            {
                auto sample = buffer.getReadPointer (channel)[j];
                double sam = (double) sample;
                // feed samples as input voltage
                VinPtr->setVoltage(sam);
                
                // get upgoing waves
                circuit->WaveUp();
                
                // set downgoing waves
                circuit->WaveDown(0);
                
                // correct attenuation
                double makeupGain = 200;
                channelData[j] = VoutPtr->Voltage()*makeupGain;
            }
        } else
        {
            memcpy (channelData,
                    buffer.getReadPointer (0),
                    buffer.getNumSamples() * sizeof (float));
        }
    }
}

//==============================================================================
bool WdftemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WdftemplateAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor (this);
}

//==============================================================================
void WdftemplateAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    std::unique_ptr<XmlElement> xml (new XmlElement ("RLCLP"));
    xml->setAttribute ("mpCutoff", (double)*mpCutoff);
    xml->setAttribute ("mpDamp", (double)*mpDamp);
    copyXmlToBinary (*xml, destData);
}

void WdftemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState.get () != nullptr)
    {
        if (xmlState->hasTagName ("RLCLP"))
        {
            *mpCutoff = xmlState->getDoubleAttribute ("mpCutoff", 10e3);
            *mpDamp = xmlState->getDoubleAttribute ("mpDamp", 0.3);
        }
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WdftemplateAudioProcessor();
}


//____________________________________________________________________________________

void WdftemplateAudioProcessor::setParameters(float freq, float damp){
    fc = freq;
    df = damp;
    wc = 2*double_Pi*fc;
    
    L1val = square(1/wc)/C1val;
    L1Ptr->setPortRes(2*fs*L1val);
    R1val = 1/(2*df)*sqrt(L1val/C1val);
    VoutPtr->setPortRes(R1val);
    
}
