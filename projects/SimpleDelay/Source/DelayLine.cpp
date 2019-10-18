#include "DelayLine.h"

namespace ampify
{

DelayLine::~DelayLine ()
{
    deallocate ();
}

void DelayLine::releaseResources ()
{
    deallocate ();
}

void DelayLine::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused (sampleRate, samplesPerBlock);
    allocate ();
}

void DelayLine::process (AudioBuffer<float> & buffer, int channelIndex)
{
    if (channelIndex >= buffer.getNumChannels ())
    {
        jassertfalse;
        return;
    }
    
    auto channelPointer = buffer.getWritePointer (channelIndex);
    if (channelPointer == nullptr)
    {
        jassertfalse;
        return;
    }
    
    // Lets do some processing!!
}

void DelayLine::setDelayTimeInSamples (int delayTimeInSamples)
{
    ignoreUnused (delayTimeInSamples);
}

void DelayLine::allocate ()
{
    
}

void DelayLine::deallocate ()
{

}


}
