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
    ignoreUnused (samplesPerBlock);
    allocate (sampleRate);
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
    
    for (int sample = 0, maxSamples = buffer.getNumSamples (); sample < maxSamples; ++sample)
    {
        auto readSample  = *channelPointer;
        auto writeSample = *_readHead;
    
        *_writeHead = readSample;
        *channelPointer = writeSample * 0.5f + readSample * 0.5f;

        if (++_writeHead >= _bufferEnd)
            _writeHead = _delayBuffer;
        
        if (++_readHead >= _bufferEnd)
            _readHead = _delayBuffer;
        
        ++channelPointer;
    }
}

void DelayLine::setDelayTimeInSamples (int delayTimeInSamples)
{
    _readHead = _writeHead;
    for (int sample = 0; sample < delayTimeInSamples; ++sample)
    {
        --_readHead;
        if (_readHead < _delayBuffer)
            _readHead = _bufferEnd;
    }
}

void DelayLine::allocate (double sampleRate)
{
    if (_delayBuffer != nullptr)
        deallocate ();
    
    _maxBufferSize = roundToInt (sampleRate * 5);
    
    _delayBuffer = new float [roundToInt (_maxBufferSize)];
    memset (_delayBuffer, 0, sizeof (float) * _maxBufferSize);
    
    _bufferEnd = _delayBuffer + _maxBufferSize - 1;
    _writeHead = _delayBuffer;
    _readHead  = _delayBuffer;
}

void DelayLine::deallocate ()
{
    if (_delayBuffer != nullptr)
    {
        delete [] _delayBuffer;
        _delayBuffer = nullptr;
    }
}


}
