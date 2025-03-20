/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// Here, the : followed by an AudioProcessor constructor call creates that class first. params(apvts) is also in the initializer list
SimpleDelayPluginAudioProcessor::SimpleDelayPluginAudioProcessor() : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true)), params(apvts)
{
    result = juce::File("C:/Users/mbase/Downloads/D2_HRIR_WAV/D2_HRIR_WAV/44K_16bit/azi_99,0_ele_35,3.wav");
}

SimpleDelayPluginAudioProcessor::~SimpleDelayPluginAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleDelayPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleDelayPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDelayPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleDelayPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleDelayPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleDelayPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleDelayPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleDelayPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleDelayPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleDelayPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SimpleDelayPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    params.prepareToPlay(sampleRate);
    params.reset();

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    // Set up convolution reverb:
    conv.reset();
    conv.prepare(spec);

}

void SimpleDelayPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleDelayPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void SimpleDelayPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, [[maybe_unused]]juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    params.update();

    // Load in the IR
    

    // Update the convolution object
    conv.reset();
    conv.prepare(spec);
    conv.loadImpulseResponse(result, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, result.getSize(), juce::dsp::Convolution::Normalise::yes);

    // Turn JUCE buffer into an AudioBlock
    juce::dsp::AudioBlock<float> block{ buffer };

    // If there is an IR, process
    if (conv.getCurrentIRSize() > 0) {
        conv.process(juce::dsp::ProcessContextReplacing<float>(block));
        //DBG("Processed IR Stats:");
        //DBG(conv.getCurrentIRSize());
        //DBG(conv.getLatency());
        //DBG(block.getNumSamples());
    }
    else {
        //DBG("Bad IR");
    }

    float sampleRate = float(getSampleRate());
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
        params.smoothen();

        channelDataL[sample] = channelDataL[sample] * params.gain;
        channelDataR[sample] = channelDataR[sample] * params.gain;
    }
    
}

//==============================================================================
bool SimpleDelayPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

// The PluginProcessor creates an instance of the Editor here
juce::AudioProcessorEditor* SimpleDelayPluginAudioProcessor::createEditor()
{
    return new SimpleDelayPluginAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleDelayPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    copyXmlToBinary(*apvts.copyState().createXml(), destData);
    DBG(apvts.copyState().toXmlString());
}

void SimpleDelayPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName(apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleDelayPluginAudioProcessor();
}
