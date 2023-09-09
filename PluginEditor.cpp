/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DelayPluginAudioProcessorEditor::DelayPluginAudioProcessorEditor (DelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    delayTime.setRange(6000.0f, 48000.0f, 100.0f);
    delayTime.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    delayTime.setTextBoxStyle(juce:: Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(delayTime);

    feedback.setRange(0.0f, 0.9f, 0.05f);
    feedback.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    feedback.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(feedback);


    delayTime.onValueChange = [this]()
    {
        audioProcessor.delay.setDelay((float)delayTime.getValue());
    };

    feedback.onValueChange = [this]()
    {
        audioProcessor.feedback = ((float)feedback.getValue());
    };

}

DelayPluginAudioProcessorEditor::~DelayPluginAudioProcessorEditor()
{
}

//==============================================================================
void DelayPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
}

void DelayPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    delayTime.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
    feedback.setBounds(delayTime.getX() + 10, delayTime.getY(),100,200);
    
}
