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
    double fs = getSampleRate();
    fc = 100;           // Cutoff Freq
    df = 0.5;           // Dampening Factor
    wc = 2*double_Pi*fc; //
    double C1val = 3.5e-5;
    C C1 = new C(1/(2*C1val*fs));
    double L1val = 1/(square(wc)*C1val);
    L L1 = new L(2*fs*L1val);
    double R1val = 1/(2*df)*sqrt(L1val/C1val);
    Vout = new R(R1val);
    Vin = new V(0,1);
    par p1 = new par(L1,Vout);
    ser s1 = new ser(Vin,p1);
    circuit = new ser(s1,C1);
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
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                Vin.setVoltage(buffer.getSample(sample, channel));
                circuit.WaveUp();
                circuit.setWD(0);
                channelData[sample] = Vout.getVoltage();
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
    return new WdftemplateAudioProcessorEditor (*this);
}

//==============================================================================
void WdftemplateAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WdftemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WdftemplateAudioProcessor();
}
