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

static juce::String stringFromDegrees(float value, int) 
{
    return juce::String(int(value)) + " degrees";
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, gainParamID, gainParam);
    castParameter(apvts, elevationParamID, elevationParam);
    castParameter(apvts, azimuthParamID, azimuthParam);
}

//return type here is ParameterLayout, this is an implementation of createParameterLayout()
juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(gainParamID, "Output Gain", juce::NormalisableRange<float>{-12.0f, 12.0f}, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>(elevationParamID, "Elevation", juce::NormalisableRange<float>{minElevation, maxElevation}, 90.0f, juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDegrees)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(azimuthParamID, "Azimuth", juce::NormalisableRange<float>{minAzimuth, maxAzimuth}, 180.0f , juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDegrees)));

    return layout;
}

void Parameters::update() noexcept 
{
    // Gain uses a linear smoother
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    azimuthSmoother.setTargetValue(azimuthParam->get());
    elevationSmoother.setTargetValue(azimuthParam->get());
}

void Parameters::prepareToPlay(double sampleRate) noexcept 
{
    double duration = 0.02;
    gainSmoother.reset(sampleRate, duration);
    azimuthSmoother.reset(sampleRate, duration);
    elevationSmoother.reset(sampleRate, duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    elevation = 0.0f;
    azimuth = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    azimuthSmoother.setCurrentAndTargetValue(azimuthParam->get());
    elevationSmoother.setCurrentAndTargetValue(elevationParam->get());
}

void Parameters::smoothen() noexcept 
{
    gain = gainSmoother.getNextValue();
    azimuth = azimuthSmoother.getNextValue();
    elevation = elevationSmoother.getNextValue();
}