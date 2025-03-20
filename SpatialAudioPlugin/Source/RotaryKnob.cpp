/*
  ==============================================================================

    RotaryKnob.cpp
    Created: 18 Mar 2025 6:01:22pm
    Author:  mbase

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RotaryKnob.h"

//==============================================================================
//Go ahead and call constructor for the variable SliderAttachment attachment here
RotaryKnob::RotaryKnob(const juce::String& text, juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& parameterID) : attachment(apvts, parameterID.getParamID(), slider)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 16);
    slider.setBounds(0, 0, 70, 86);
    addAndMakeVisible(slider);

    label.setText(text, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>{0, 0, 2, 0});
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);

    setSize(70, 110);
}

RotaryKnob::~RotaryKnob()
{
}

void RotaryKnob::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
}

void RotaryKnob::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    slider.setTopLeftPosition(0, 24);
}
