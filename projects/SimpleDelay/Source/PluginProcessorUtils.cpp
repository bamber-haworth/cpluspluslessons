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
