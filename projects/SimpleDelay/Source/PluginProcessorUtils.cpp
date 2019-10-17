#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDelayAudioProcessor::SimpleDelayAudioProcessor ()
    : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true))
{
}

SimpleDelayAudioProcessor::~SimpleDelayAudioProcessor ()
{
}

bool SimpleDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout & layouts) const
{
    if ((layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()) ||
        layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

AudioProcessorEditor* SimpleDelayAudioProcessor::createEditor()
{
    return new SimpleDelayAudioProcessorEditor (*this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDelayAudioProcessor();
}
