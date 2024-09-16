#include "CustomLookAndFeel.h"

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                         float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    int frameWidth = 64;
    int frameHeight = 64;
    int frameToDraw = static_cast<int>(sliderPos * numFramesInAnimation) % numFramesInAnimation;

    g.drawImage(knobImage, x, y, width, height,
                0, frameToDraw * frameHeight, frameWidth, frameHeight);
}
