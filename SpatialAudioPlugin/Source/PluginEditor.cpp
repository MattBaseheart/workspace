/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleDelayPluginAudioProcessorEditor::SimpleDelayPluginAudioProcessorEditor (SimpleDelayPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(gainKnob);
    addAndMakeVisible(azimuthKnob);
    addAndMakeVisible(elevationKnob);
    setSize (500, 330);
}

SimpleDelayPluginAudioProcessorEditor::~SimpleDelayPluginAudioProcessorEditor()
{
}

//==============================================================================
void SimpleDelayPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));

    juce::Value valueToControl;
}

void SimpleDelayPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    elevationKnob.setTopLeftPosition(20, 10);
    azimuthKnob.setTopLeftPosition(elevationKnob.getRight() + 20, 10);
    gainKnob.setTopLeftPosition(azimuthKnob.getRight() + 20, 10);
    
}
