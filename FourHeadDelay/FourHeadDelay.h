/*
  ==============================================================================

    FourHeadDelay.h
    Created: 8 Sep 2023 10:48:45pm
    Author:  vngel

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FourHeadDelay
{
private:
    
    struct DelayHead
    {
        
        juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delay{96000};
        float currentDelay;
        float delayTarget;
        float feedback;
       
        float process(int channel,float inSample)
        {
            
            float outSample;

            //delay.setDelay(currentDelay);

            outSample = delay.popSample(channel);

            delay.pushSample(channel, (feedback * outSample) + inSample);

            return outSample;

        }


    };
    
   
   
public:
    FourHeadDelay()
    {
        this->feedback = 0;
        this->sampleRate = 44100.0f;
        this->bpm = 0;
        this->getBpm = false;
    }

    FourHeadDelay(float sampleRate)
    {
        this->feedback = 0;
        this->sampleRate = sampleRate;
    }

    void prepare(const juce::dsp::ProcessSpec& spec) 
    {

        this->sampleRate = spec.sampleRate;

        for (int i = 0; i < 4; i++)
        {
            heads[i].delay.reset();
            heads[i].delay.prepare(spec);
        }
    }

    float process(int channel, float in)
    {
 

        float allDelaySignals = 0;

        for (int i = 0; i < 4; i++)
        {
            heads[i].feedback = this->feedback;
            heads[i].delay.setDelay((i + 0.25 - i * 0.75) * (this->sampleRate * (60 / bpm)));
            if (headState[i] == true)
                allDelaySignals += heads[i].process(channel,in);
        }

        return allDelaySignals;
     
    }
    void setFeedback(float feedback)
    {
        this->feedback = feedback;
    }
    void setSampleRate(float sampleRate)
    {
        this->sampleRate = sampleRate;
    }
    void toggleHead(int headNumber)
    {
        // Check for valid index
        if (headNumber > 3 || headNumber < 0)
            return;

        // Flip state of delay head
        headState[headNumber] = !headState[headNumber];
    }
    void setBpm(double bpm)
    {
        this->bpm = bpm;
    }
    bool getBpmFlag()
    {
        return getBpm;
    }
    void toggleBpmHostFlag()
    {
        getBpm = !getBpm;
    }
private:
    DelayHead heads[4];
    bool headState[4] = {false,false,false,false};
    float feedback;
    float sampleRate;
    double bpm;
    bool getBpm;

};