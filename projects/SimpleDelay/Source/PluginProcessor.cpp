#include "PluginProcessor.h"

double SimpleDelayAudioProcessor::getTailLengthSeconds () const
{
    return 0.0;
}

void SimpleDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void SimpleDelayAudioProcessor::releaseResources ()
{

}

void SimpleDelayAudioProcessor::processBlock (AudioBuffer<float> & buffer, MidiBuffer & midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}