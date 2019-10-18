#include "PluginProcessor.h"

SimpleDelayAudioProcessor::SimpleDelayAudioProcessor ()
    : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true))
{
    addParameter (_delayTime = new AudioParameterChoice ("delayTime",
                                                         "Delay Time",
                                                         _delayTimeCalculator.getTimeDivisions (),
                                                         _delayTimeCalculator.getDefaultTempoDivisionIndex ()));
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
    _delayTimeCalculator.setSampleRate (float (sampleRate));
    
    for (int delayIndex = 0; delayIndex < numberOfChannelsOfDelay; ++delayIndex)
        _delayLines[delayIndex].prepareToPlay (sampleRate, samplesPerBlock);
}

void SimpleDelayAudioProcessor::releaseResources ()
{
    for (int delayIndex = 0; delayIndex < numberOfChannelsOfDelay; ++delayIndex)
        _delayLines[delayIndex].releaseResources ();
}

void SimpleDelayAudioProcessor::processBlock (AudioBuffer<float> & buffer, MidiBuffer & midiMessages)
{
    ignoreUnused (midiMessages);

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = std::min<int> (numberOfChannelsOfDelay, getTotalNumInputChannels ());
    auto totalNumOutputChannels = std::min<int> (numberOfChannelsOfDelay, getTotalNumOutputChannels ());

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto delayTimeInSamples = computeDelayTimeInSamples ();
    if (delayTimeInSamples <= 0)
    {
        jassertfalse;
        return;
    }

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        _delayLines[channel].setDelayTimeInSamples (delayTimeInSamples);
        _delayLines[channel].process (buffer, channel);
    }
}
