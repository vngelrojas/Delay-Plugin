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
    
    // Delay time slider
    delayTime.setRange(6000.0f, 48000.0f, 100.0f);
    delayTime.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    delayTime.setTextBoxStyle(juce:: Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(delayTime);

    // Feedback slider
    feedback.setRange(0.0f, 0.9f, 0.05f);
    feedback.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    feedback.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(feedback);

    // Delay head toggle buttons
    for (int i = 0; i < 4; i++)
    {
        headToggles[i].setButtonText("head " + std::to_string(1 + i));
        addAndMakeVisible(headToggles[i]);
        headToggles[i].onClick = [this,i]()
        {
            audioProcessor.fourHead.toggleHead(i);
        };
    }


    delayTime.onValueChange = [this]()
    {
        
        audioProcessor.fourHead.setSampleRate((float)delayTime.getValue());
    };

    feedback.onValueChange = [this]()
    {
        audioProcessor.fourHead.setFeedback((float)feedback.getValue());
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
    for (int i = 0; i < 4; i++)
    {
        headToggles[i].setBounds(delayTime.getX() + 50 + i * 50, delayTime.getY() - 40, 50, 50);
    }
    
}
