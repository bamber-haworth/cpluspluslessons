#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleDelayAudioProcessorEditor::SimpleDelayAudioProcessorEditor (SimpleDelayAudioProcessor & p)
    : AudioProcessorEditor (&p)
    , processor (p)
{
    setSize (400, 300);
}

void SimpleDelayAudioProcessorEditor::paint (Graphics & g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SimpleDelayAudioProcessorEditor::resized ()
{

}
