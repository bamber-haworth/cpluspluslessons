#include "PluginProcessor.h"
#include "PluginEditor.h"

bool SimpleDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout & layouts) const
{
    if ((layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()) ||
        layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

AudioProcessorEditor * SimpleDelayAudioProcessor::createEditor ()
{
    return new SimpleDelayAudioProcessorEditor (*this);
}

AudioParameterChoice & SimpleDelayAudioProcessor::getDelayTimeParameter ()
{
    jassert (_delayTime != nullptr);
    return *_delayTime;
}

AudioProcessor * JUCE_CALLTYPE createPluginFilter ()
{
    return new SimpleDelayAudioProcessor ();
}
