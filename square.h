/*
  ==============================================================================

    square.h
    Created: 8 Aug 2022 8:04:48am
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "constants.h"


class square  : public juce::Component
{
public:
    bool road = false, depot = false;

    square()
    {
        setSize (squareSize, squareSize);
    }

    ~square() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::lightgreen);

        if (road)
        {
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(1, 1, squareSize - 2, squareSize - 2);
        }

        if (depot)
        {
            g.setColour(juce::Colours::brown);
            g.fillRect(1, 1, squareSize - 2, squareSize - 2);
        }

        int thickness;
        if (chosen)
        {
            thickness = 2;
            g.setColour(juce::Colours::darkgrey);
        }
        else
        {
            thickness = 1;
            g.setColour(juce::Colours::grey);
        }
        g.drawRect(0, 0, squareSize, squareSize, thickness);
    }

    void resized() override
    {

    }

    void mouseEnter (const juce::MouseEvent& event) override
    {
        chosen = true;
        repaint();
    }

    void mouseExit (const juce::MouseEvent& event) override
    {
        chosen = false;
        repaint();
    }

    void mouseDown (const juce::MouseEvent& event) override
    {
        road = !road;
        repaint();
    }

    void mouseDoubleClick (const juce::MouseEvent& event) override
    {
        depot = !depot;
        repaint();
    }


private:
    bool chosen;

};
