#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


namespace ampify
{


class DelayLine
{
public:

    DelayLine () = default;
    DelayLine (const DelayLine & other) = delete;
    ~DelayLine ();

    const DelayLine & operator = (const DelayLine & other) = delete;
    bool operator == (const DelayLine & other) const = delete;
    bool operator != (const DelayLine & other) const = delete;
    
    void setDelayTimeInSamples (int delayTimeInSamples);
    
    void releaseResources ();
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void process (AudioBuffer<float> & buffer, int channelIndex);

private:
    
    void allocate (double sampleRate);
    void deallocate ();
    
    int _maxBufferSize = 0;
    float * _delayBuffer = nullptr;
    float * _bufferEnd = nullptr;
    float * _writeHead = nullptr;
    float * _readHead = nullptr;
};


}
