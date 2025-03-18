/*
  ==============================================================================

    Parameters.cpp
    Created: 2 Mar 2025 3:09:12pm
    Author:  mbase

  ==============================================================================
*/

#include "Parameters.h"

template<typename T>
static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination) 
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);
}

static juce::String stringFromDecibels(float value, int) {
    //Display 1 decimal place
    return juce::String(value, 1) + "dB";
}

//String from value function for Delay Time
static juce::String stringFromMilliseconds(float value, int) {
    //Display 2 decimal places
    if (value < 10.0f) {
        return juce::String(value, 2) + "ms";
    }
    //Display 1 decimal place
    else if(value < 100.0f){
        return juce::String(value, 1) + "ms";
    }
    //Display no decimal place
    else if (value < 1000.0f) {
        return juce::String(int(value)) + "ms";
    }
    //Display in seconds
    else {
        return juce::String(value * 0.001f, 2) + "s";
    }
}

static juce::String stringFromPercent(float value, int) 
{
    return juce::String(int(value)) + " %";
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, gainParamID, gainParam);
    castParameter(apvts, delayTimeParamID, delayTimeParam);
    castParameter(apvts, mixParamID, mixParam);
}

//return type here is ParameterLayout, this is an implementation of createParameterLayout()
juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(gainParamID, "Output Gain", juce::NormalisableRange<float>{-12.0f, 12.0f}, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(delayTimeParamID, "Delay Time", juce::NormalisableRange<float>{minDelayTime, maxDelayTime, 0.001f, 0.25f}, 100.0f, juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromMilliseconds)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(mixParamID, "Mix", juce::NormalisableRange<float>{0.0f, 100.0f , 1.0f}, 100.0f, juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    return layout;
}

void Parameters::update() noexcept 
{
    // Gain uses a linear smoother
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    mixSmoother.setTargetValue(mixParam->get() * 0.01f);

    //Delay uses exponential (one-pole) smoother
    targetDelayTime = delayTimeParam->get();
    if (delayTime == 0.0f) {
        delayTime = targetDelayTime;
    }
}

void Parameters::prepareToPlay(double sampleRate) noexcept 
{
    double duration = 0.02;
    gainSmoother.reset(sampleRate, duration);
    coeff = 1.0f - std::exp(-1.0f / (0.2f * float(sampleRate)));
    mixSmoother.reset(sampleRate, duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    delayTime = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);
}

void Parameters::smoothen() noexcept 
{
    gain = gainSmoother.getNextValue();
    delayTime += (targetDelayTime - delayTime) * coeff;
    mix = mixSmoother.getNextValue();
}