#include "PluginProcessor.h"

SimpleDelayAudioProcessor::SimpleDelayAudioProcessor ()
    : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true))
{
    const StringArray choices ("1/32", "1/16", "1/8", "1/4", "1/2", "1");
    addParameter (_delayTime = new AudioParameterChoice ("delayTime", "Delay Time", choices, 2));
}

SimpleDelayAudioProcessor::~SimpleDelayAudioProcessor ()
{
}

double SimpleDelayAudioProcessor::getTailLengthSeconds () const
{
    return 0.0;
}

void SimpleDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused (sampleRate, samplesPerBlock);
}

void SimpleDelayAudioProcessor::releaseResources ()
{

}

void SimpleDelayAudioProcessor::processBlock (AudioBuffer<float> & buffer, MidiBuffer & midiMessages)
{
    ignoreUnused (midiMessages);

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto delayTimeDivision = _delayTime->getIndex ();
    ignoreUnused (delayTimeDivision);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto * channelData = buffer.getWritePointer (channel);
        ignoreUnused (channelData);
    }
}
