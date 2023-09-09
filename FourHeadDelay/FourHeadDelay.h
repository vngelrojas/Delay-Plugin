/*
  ==============================================================================

    FourHeadDelay.h
    Created: 8 Sep 2023 10:48:45pm
    Author:  vngel

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
template <typename SampleType, typename InterpolationType = juce::dsp::DelayLineInterpolationTypes::Linear>
class FourHeadDelay
{
private:
    struct DelayHead
    {
        juce::dsp::DelayLine<SampleType, InterpolationType> delay{96000};
        float currentDelay;
        float delayTarget;
        float feedback;
       
        float proccess(int channel,float inSample)
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
    void prepare(const juce::dsp::ProcessSpec& spec) 
    {
      
        for (int i = 0; i < 4; i++)
        {
            heads[i].delay.reset();
            heads[i].delay.prepare(context);
         
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
private:
    DelayHead heads [4];
    bool headState[4];
    float feedback;
    float sampleRate;

};