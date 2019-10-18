#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

namespace ampify
{

class DelayTimeCalculator
{
public:

    enum class TempoDivision
    {
        one = 0,
        half,
        quarter,
        eigth,
        sixteenth,
        thirtysecond,
    };

    DelayTimeCalculator ();
    ~DelayTimeCalculator () = default;
    
    StringArray getTimeDivisions () const;
    TempoDivision getDefaultTempoDivision () const;
    String getDefaultTempoDivisionString () const;
    int getDefaultTempoDivisionIndex () const;
    
    void setSampleRate (float sampleRate);
    
    int getDelayTimeInSamples (float tempo, TempoDivision division) const;
    int getDelayTimeInSamples (float tempo, int division) const;

private:
    
    static constexpr int numberOfTempoDivisions = int (TempoDivision::thirtysecond) + 1;
    
    float getDelayTimeInMilliseconds (float tempo, TempoDivision division) const;
    float getDivisorForDivision (TempoDivision division) const;
    
    std::map<TempoDivision, String> _tempoDivisionMap;
    float _sampleRate = 44100.f;
};

}
