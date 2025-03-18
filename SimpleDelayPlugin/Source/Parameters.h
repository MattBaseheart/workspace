/*
  ==============================================================================

    Parameters.h
    Created: 2 Mar 2025 3:09:12pm
    Author:  mbase

  ==============================================================================
*/

//Read the Parameters.h ONLY ONCE even if it is referenced in multiple files
#pragma once

// Tells the C++ compiler what juce:: means
#include <JuceHeader.h>

// Create parameters as constants + tie a PID to it
const juce::ParameterID gainParamID{ "gain", 1 };
const juce::ParameterID delayTimeParamID{ "delayTime", 1 };
const juce::ParameterID mixParamID{ "mix", 1 };

class Parameters 
{
public:

    Parameters(juce::AudioProcessorValueTreeState& apvts);

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void update() noexcept;
    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void smoothen() noexcept;

    float gain = 0.0f;
    float delayTime = 0.0f;
    float mix = 1.0f;

    static constexpr float minDelayTime = 5.0f;
    static constexpr float maxDelayTime = 5000.0f;

private:
    // Gain Param is done with Linear Smoothing
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
    juce::AudioParameterFloat* mixParam;
    juce::LinearSmoothedValue<float> mixSmoother;

    //Delay Param is done with Exponential (one-pole) smoothing
    juce::AudioParameterFloat* delayTimeParam;
    float targetDelayTime = 0.0f; // Value the smoothing filter is trying to reach
    float coeff = 0.0f; //How fast the smoothing happens

    //Only allow one unique instance of this class, and include leak detector
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)

};
