#pragma once

#include <JuceHeader.h>
#include "square.h"

const int width = 600, height = 400;

class map : public juce::Component
{
public:
    map()
    {
        setSize(width, height);

        for (int i = 0; i < width / squareSize; i++)
            for (int j = 0; j < height / squareSize; j++)
            {
                addChildComponent(s[i][j]);
                addAndMakeVisible(s[i][j]);
            }
    }

    ~map() override
    {

    }

    void paint(juce::Graphics& g) override
    {

    }

    void resized() override
    {
        for (int i = 0; i < width / squareSize; i++)
            for (int j = 0; j < height / squareSize; j++)
            {
                s[i][j].setBounds(i * squareSize,
                    j * squareSize,
                    squareSize,
                    squareSize);
            }
    }


private:
    square s[width / squareSize][height / squareSize];

};