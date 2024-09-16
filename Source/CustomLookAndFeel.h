#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel(juce::Image knobImage)
        : knobImage(knobImage)
    {
        numFramesInAnimation = knobImage.getHeight() / 64; // Asumsi setiap frame knob berukuran 64x64
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                         float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

    int getNumFramesInAnimation() const { return numFramesInAnimation; }

private:
    juce::Image knobImage;
    int numFramesInAnimation;
};
