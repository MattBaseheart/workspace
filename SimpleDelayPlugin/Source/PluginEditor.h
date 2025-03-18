/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Parameters.h"

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
    
    juce::Slider slider;
    juce::Label label;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment { audioProcessor.apvts, gainParamID.getParamID(), slider };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleDelayPluginAudioProcessorEditor)
};
