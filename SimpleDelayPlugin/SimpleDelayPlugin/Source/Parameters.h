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
private:
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
};
