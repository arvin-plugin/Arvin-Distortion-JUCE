#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
ArvinDistortionAudioProcessorEditor::ArvinDistortionAudioProcessorEditor(ArvinDistortionAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), currentAnimationFrame(0)
{
    setSize(200, 359);

    // Load the background image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

    // Load the knob images
    knobImage1 = juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
    knobImage2 = juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);

    // Setup knob sliders with custom LookAndFeel
    addAndMakeVisible(knobSlider1);
    knobSlider1.setSliderStyle(juce::Slider::Rotary);
    knobSlider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobSlider1.setRange(0.0, 1.0);
    knobSlider1.setValue(*audioProcessor.getDistortionLevel());
    knobSlider1.addListener(this);

    addAndMakeVisible(knobSlider2);
    knobSlider2.setSliderStyle(juce::Slider::Rotary);
    knobSlider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    knobSlider2.setRange(0.0, 1.0);
    knobSlider2.setValue(*audioProcessor.getOutputVolume());
    knobSlider2.addListener(this);

    // Pass knobImage reference to CustomLookAndFeel
    customLookAndFeel1 = std::make_unique<CustomLookAndFeel>(knobImage1);
    knobSlider1.setLookAndFeel(customLookAndFeel1.get());

    // Pass knobImage reference to CustomLookAndFeel for the second knob
    customLookAndFeel2 = std::make_unique<CustomLookAndFeel>(knobImage2);
    knobSlider2.setLookAndFeel(customLookAndFeel2.get());
}

ArvinDistortionAudioProcessorEditor::~ArvinDistortionAudioProcessorEditor()
{
    knobSlider1.setLookAndFeel(nullptr);
    knobSlider2.setLookAndFeel(nullptr);
}

void ArvinDistortionAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Draw the background image
    if (!backgroundImage.isNull())
        g.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void ArvinDistortionAudioProcessorEditor::resized()
{
    // Set bounds for the sliders
    knobSlider1.setBounds(20, 40, 64, 64);
    knobSlider2.setBounds(110, 40, 64, 64);
}

void ArvinDistortionAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &knobSlider1)
    {
        *audioProcessor.getDistortionLevel() = knobSlider1.getValue();
    }
    else if (slider == &knobSlider2)
    {
        *audioProcessor.getOutputVolume() = knobSlider2.getValue();
    }

    // Update animation frame when slider value changes
    // No need for dynamic_cast if you handle LookAndFeel references directly
    repaint();
}
