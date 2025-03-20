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
const juce::ParameterID azimuthParamID{ "azimuth", 1 };
const juce::ParameterID elevationParamID{ "elevation", 1 };

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
    float elevation = 0.0f;
    float azimuth = 1.0f;

    static constexpr float minElevation = 0.0f;
    static constexpr float maxElevation = 180.0f;
    static constexpr float minAzimuth = 0.0f;
    static constexpr float maxAzimuth = 360.0f;

private:
    // Gain Param is done with Linear Smoothing
    juce::AudioParameterFloat* gainParam;
    juce::LinearSmoothedValue<float> gainSmoother;
    juce::AudioParameterFloat* azimuthParam;
    juce::LinearSmoothedValue<float> azimuthSmoother;
    juce::AudioParameterFloat* elevationParam;
    juce::LinearSmoothedValue<float> elevationSmoother;

    //Only allow one unique instance of this class, and include leak detector
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Parameters)

};
