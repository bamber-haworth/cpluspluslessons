#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDelayAudioProcessorEditor::SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor & processor)
    : AudioProcessorEditor (&processor)
    , _processor (processor)
{
    setSize (400, 300);
    
    addAndMakeVisible (_delayTime);
    
//    _delayTime.addItemList (_processor.getDelayTimeParameter ().choices, 1);
//    _delayTime.setSelectedId (_processor.getDelayTimeParameter ().getIndex () + 1);
//    _delayTime.onChange = [this] ()
//    {
//        auto newDelayTime = _delayTime.getText ();
//        auto & parameter = _processor.getDelayTimeParameter ();
//        if (parameter.getCurrentValueAsText () != newDelayTime)
//        {
//            auto * baseParameter = (AudioProcessorParameter *)&parameter;
//            baseParameter->beginChangeGesture ();
//            baseParameter->setValueNotifyingHost (baseParameter->getValueForText (newDelayTime));
//            baseParameter->endChangeGesture ();
//        }
//    };
}

void SimpleDelayAudioProcessorEditor::paint (Graphics & g)
{
    g.fillAll (getLookAndFeel ().findColour (ResizableWindow::backgroundColourId));
}

void SimpleDelayAudioProcessorEditor::resized ()
{
    _delayTime.setBounds (10, 10, getWidth () - 20, 25);
}
