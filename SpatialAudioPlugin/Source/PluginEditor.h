/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"
#include "RotaryKnob.h"

//==============================================================================
/**
*/
class SimpleDelayPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SimpleDelayPluginAudioProcessorEditor (SimpleDelayPluginAudioProcessor&);
    ~SimpleDelayPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleDelayPluginAudioProcessor& audioProcessor;
    juce::Value valueToControl;
    
    RotaryKnob gainKnob{ "Gain", audioProcessor.apvts, gainParamID };
    RotaryKnob azimuthKnob{ "Azimuth", audioProcessor.apvts, azimuthParamID };
    RotaryKnob elevationKnob{ "Elevation", audioProcessor.apvts, elevationParamID };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayPluginAudioProcessorEditor)
};
