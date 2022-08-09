/*
  ==============================================================================

    car.h
    Created: 8 Aug 2022 8:04:42am
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "constants.h"
#include <unistd.h>



class Car : public juce::Component
{
public:
    int x = 0, y = 0;

    Car ()
    {
        setSize(squareSize, squareSize);
    }

    void paint (juce::Graphics& g) override
    {
        g.setColour(juce::Colours::yellow);
        g.fillRect(5, 5, squareSize - 10, squareSize - 10);
    }
};
