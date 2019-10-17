#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleDelayAudioProcessor  : public AudioProcessor
{
public:

    SimpleDelayAudioProcessor ();
    ~SimpleDelayAudioProcessor ();

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout & layouts) const override;
   #endif

    void processBlock (AudioBuffer<float> &, MidiBuffer &) override;

    AudioProcessorEditor* createEditor () override;
    bool hasEditor () const override { return true; }

    const String getName () const override { return JucePlugin_Name; }

    bool acceptsMidi () const override { return false; }
    bool producesMidi () const override { return false; }
    bool isMidiEffect () const override { return false; }
    double getTailLengthSeconds () const override;

    int getNumPrograms () override { return 1;  }
    int getCurrentProgram () override { return 0; }
    void setCurrentProgram (int index) override { ignoreUnused (index); }
    const String getProgramName (int index) override { ignoreUnused (index); return ""; }
    void changeProgramName (int index, const String & newName) override { ignoreUnused (index, newName); }

    void getStateInformation (MemoryBlock & destData) override { ignoreUnused (destData); }
    void setStateInformation (const void * data, int sizeInBytes) override { ignoreUnused (data, sizeInBytes); }
    
    // What is the danger here??
    AudioParameterChoice & getDelayTimeParameter ();

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessor)
    
    AudioParameterChoice * _delayTime = nullptr;
};
