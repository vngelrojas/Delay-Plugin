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

    waveZoom.setRange(12000.0f, 48000.0f, 100.0f);
    waveZoom.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    waveZoom.setTextBoxStyle(juce:: Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(waveZoom);

    waveZoom.onValueChange = [this]()
    {
        audioProcessor.delay.setDelay((float)waveZoom.getValue());
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
    waveZoom.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
}
