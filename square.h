#pragma once

#include <JuceHeader.h>

const int squareSize = 20;

class square : public juce::Component
{
public:
    square()
    {
        setSize(squareSize, squareSize);

        addMouseListener(this, true);
    }

    ~square() override
    {

    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::palegreen);

        g.setColour(juce::Colours::lightgrey);
        juce::Rectangle<float> rect(squareSize, squareSize);
        g.drawRect(rect, 1.0f);
    }

    void resized() override
    {

    }



private:
    int X; int Y;

    bool depot = 0; bool road = 0;
};