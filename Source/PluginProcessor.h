#pragma once

#include <JuceHeader.h>

//==============================================================================
class ArvinDistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    // Getter untuk distortionLevel
    juce::AudioParameterFloat* getDistortionLevel() { return distortionLevel; }

    // Getter untuk outputVolume
    juce::AudioParameterFloat* getOutputVolume() { return outputVolume; }
    //==============================================================================
    ArvinDistortionAudioProcessor();
    ~ArvinDistortionAudioProcessor() override;

    //==============================================================================
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    bool hasEditor() const override;
    juce::AudioProcessorEditor* createEditor() override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    // Distortion level and output volume parameters
    juce::AudioParameterFloat* distortionLevel;
    juce::AudioParameterFloat* outputVolume;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArvinDistortionAudioProcessor)
};
