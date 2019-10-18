#include "DelayTimeCalculator.h"

namespace ampify
{

DelayTimeCalculator::DelayTimeCalculator ()
{
    _tempoDivisionMap =
    {
        std::make_pair (DelayTimeCalculator::TempoDivision::one, "1"),
        std::make_pair (DelayTimeCalculator::TempoDivision::half, "1/2"),
        std::make_pair (DelayTimeCalculator::TempoDivision::quarter, "1/4"),
        std::make_pair (DelayTimeCalculator::TempoDivision::eigth, "1/8"),
        std::make_pair (DelayTimeCalculator::TempoDivision::sixteenth, "1/16"),
        std::make_pair (DelayTimeCalculator::TempoDivision::thirtysecond, "1/32"),
    };
}

StringArray DelayTimeCalculator::getTimeDivisions () const
{
    StringArray divisions;
    
    for (int division = 0; division < numberOfTempoDivisions; ++division)
        divisions.add (_tempoDivisionMap.at (DelayTimeCalculator::TempoDivision (division)));
    
    return divisions;
}

DelayTimeCalculator::TempoDivision DelayTimeCalculator::getDefaultTempoDivision () const
{
    return DelayTimeCalculator::TempoDivision::eigth;
}

String DelayTimeCalculator::getDefaultTempoDivisionString () const
{
    return _tempoDivisionMap.at (getDefaultTempoDivision ());
}

int DelayTimeCalculator::getDefaultTempoDivisionIndex () const
{
    auto index = getTimeDivisions ().indexOf (getDefaultTempoDivisionString ());
    if (index < 0)
    {
        jassertfalse;
        return 0;
    }
    return index;
}

void DelayTimeCalculator::setSampleRate (float sampleRate)
{
    _sampleRate = sampleRate;
}

float DelayTimeCalculator::getDivisorForDivision (TempoDivision division) const
{
    switch (division)
    {
        case DelayTimeCalculator::TempoDivision::one:           return 1;
        case DelayTimeCalculator::TempoDivision::half:          return 0.5f;
        case DelayTimeCalculator::TempoDivision::quarter:       return 0.25f;
        case DelayTimeCalculator::TempoDivision::eigth:         return 0.125f;
        case DelayTimeCalculator::TempoDivision::sixteenth:     return 0.0625f;
        case DelayTimeCalculator::TempoDivision::thirtysecond:  return 0.03125f;
    }
    
    jassertfalse;
    return 1.f;
}

float DelayTimeCalculator::getDelayTimeInMilliseconds (float tempo, TempoDivision division) const
{
    return (60000 / tempo) * getDivisorForDivision (division);
}

int DelayTimeCalculator::getDelayTimeInSamples (float tempo, TempoDivision division) const
{
    return roundToInt ((getDelayTimeInMilliseconds (tempo, division) / 1000.0) * _sampleRate);
}

int DelayTimeCalculator::getDelayTimeInSamples (float tempo, int division) const
{
    return getDelayTimeInSamples (tempo, DelayTimeCalculator::TempoDivision (division));
}

}
