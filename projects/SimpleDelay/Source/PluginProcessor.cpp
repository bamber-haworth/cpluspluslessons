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
    ignoreUnused (samplesPerBlock);
    _delayTimeCalculator.setSampleRate (float (sampleRate));
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
    
    auto playHead = getPlayHead ();
    if (playHead == nullptr)
    {
        jassertfalse;
        return;
    }
    
    AudioPlayHead::CurrentPositionInfo info;
    if (! playHead->getCurrentPosition (info))
    {
        jassertfalse;
        return;
    }

    auto delayTimeInSamples = _delayTimeCalculator.getDelayTimeInSamples (float (info.bpm),
                                                                          DelayTimeCalculator::TempoDivision (_delayTime->getIndex ()));
    
    ignoreUnused (delayTimeInSamples);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto * channelData = buffer.getWritePointer (channel);
        ignoreUnused (channelData);
    }
}
