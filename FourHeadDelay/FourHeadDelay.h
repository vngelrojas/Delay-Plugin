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

            delay.setDelay(currentDelay);

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

    }

    FourHeadDelay(float sampleRate)
    {
        this->feedback = 0;
        this->sampleRate = sampleRate;
    }

    void prepare(const juce::dsp::ProcessSpec& spec) 
    {
      
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
            heads[i].delayTarget = (i + 0.25 - i * 0.75) * this->sampleRate;
            if (headState[i])
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
private:
    DelayHead heads[4];
    bool headState[4] = {false,true,false,true};
    float feedback;
    float sampleRate;

};