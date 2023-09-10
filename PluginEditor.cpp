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
    delayTime.setRange(0.0f, 1000.0f, 1.0f);
    delayTime.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    delayTime.setTextBoxStyle(juce:: Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(delayTime);

    delayTime.onValueChange = [this]()
    {
       audioProcessor.fourHead.setBpm(delayTime.getValue());
    };

    // Feedback slider
    feedback.setRange(0.0f, 0.9f, 0.05f);
    feedback.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    feedback.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(feedback);

    feedback.onValueChange = [this]()
    {
        audioProcessor.fourHead.setFeedback((float)feedback.getValue());
    };

    // Dry/Wet slider
    dryWet.setRange(0.0f, 1.0f, 0.01f);
    dryWet.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    dryWet.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(dryWet);

    dryWet.onValueChange = [this]()
    {
        audioProcessor.dryWet.setWetMixProportion((float)dryWet.getValue());
    };

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
    // Get host bpm button
    hostBpmButton.setButtonText("Host BPM");
    hostBpmButton.onClick = [this]()
    {
        audioProcessor.fourHead.toggleBpmHostFlag();
    };
    addAndMakeVisible(hostBpmButton);


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

    delayTime.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
    feedback.setBounds(delayTime.getX() + 10, delayTime.getY(),100,200);
    dryWet.setBounds(feedback.getX() - 50, delayTime.getY(), 100, 200);

    for (int i = 0; i < 4; i++)
    {
        headToggles[i].setBounds(delayTime.getX() + 50 + i * 50, delayTime.getY() - 40, 50, 50);
    }
    hostBpmButton.setBounds(10, headToggles[4].getY(), 50, 50);
    
}
