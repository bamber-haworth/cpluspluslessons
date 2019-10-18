#include "PluginProcessor.h"

bool SimpleDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout & layouts) const
{
    if ((layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != AudioChannelSet::stereo()) ||
        layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

AudioProcessor * JUCE_CALLTYPE createPluginFilter ()
{
    return new SimpleDelayAudioProcessor ();
}

int SimpleDelayAudioProcessor::computeDelayTimeInSamples ()
{
    auto playHead = getPlayHead ();
    if (playHead == nullptr)
    {
        jassertfalse;
        return -1;
    }
    
    AudioPlayHead::CurrentPositionInfo info;
    if (! playHead->getCurrentPosition (info))
    {
        jassertfalse;
        return -1;
    }

    return _delayTimeCalculator.getDelayTimeInSamples (float (info.bpm), _delayTime->getIndex ());
}

constexpr int SimpleDelayAudioProcessor::numberOfChannelsOfDelay;
