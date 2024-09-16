#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class ArvinDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              public juce::Slider::Listener
{
public:
    ArvinDistortionAudioProcessorEditor (ArvinDistortionAudioProcessor&);
    ~ArvinDistortionAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    ArvinDistortionAudioProcessor& audioProcessor;

    // UI Elements
    juce::Slider knobSlider1;
    juce::Slider knobSlider2;
    juce::Image backgroundImage;
    juce::Image knobImage1;
    juce::Image knobImage2;

    std::unique_ptr<CustomLookAndFeel> customLookAndFeel1;
    std::unique_ptr<CustomLookAndFeel> customLookAndFeel2;

    int currentAnimationFrame;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArvinDistortionAudioProcessorEditor)
};
