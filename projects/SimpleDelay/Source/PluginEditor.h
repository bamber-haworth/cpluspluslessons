#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class SimpleDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:

    SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor & processor);
    ~SimpleDelayAudioProcessorEditor () = default;
    
    void paint (Graphics & g) override;
    void resized () override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayAudioProcessorEditor)
    
    SimpleDelayAudioProcessor& processor;
};
