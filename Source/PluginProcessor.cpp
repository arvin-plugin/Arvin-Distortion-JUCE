#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ArvinDistortionAudioProcessor::ArvinDistortionAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     )
{
    // Initialize parameters
    addParameter(distortionLevel = new juce::AudioParameterFloat("distortionLevel", "Distortion Level", 0.0f, 1.0f, 0.5f));
    addParameter(outputVolume = new juce::AudioParameterFloat("outputVolume", "Output Volume", 0.0f, 1.0f, 0.8f));
}

ArvinDistortionAudioProcessor::~ArvinDistortionAudioProcessor() {}

const juce::String ArvinDistortionAudioProcessor::getName() const { return JucePlugin_Name; }

bool ArvinDistortionAudioProcessor::acceptsMidi() const { return false; }
bool ArvinDistortionAudioProcessor::producesMidi() const { return false; }
bool ArvinDistortionAudioProcessor::isMidiEffect() const { return false; }
double ArvinDistortionAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int ArvinDistortionAudioProcessor::getNumPrograms() { return 1; }
int ArvinDistortionAudioProcessor::getCurrentProgram() { return 0; }
void ArvinDistortionAudioProcessor::setCurrentProgram (int) {}
const juce::String ArvinDistortionAudioProcessor::getProgramName (int) { return {}; }
void ArvinDistortionAudioProcessor::changeProgramName (int, const juce::String&) {}

void ArvinDistortionAudioProcessor::prepareToPlay (double, int) {}
void ArvinDistortionAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ArvinDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}
#endif

void ArvinDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Apply distortion and adjust volume
            float distortedSample = std::tanh(channelData[sample] * (*distortionLevel * 10.0f));
            channelData[sample] = distortedSample * *outputVolume;
        }
    }
}

bool ArvinDistortionAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* ArvinDistortionAudioProcessor::createEditor() { return new ArvinDistortionAudioProcessorEditor (*this); }

void ArvinDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}
void ArvinDistortionAudioProcessor::setStateInformation (const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new ArvinDistortionAudioProcessor(); }
