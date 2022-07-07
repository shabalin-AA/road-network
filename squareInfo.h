/*
  ==============================================================================

    squareInfo.h
    Created: 3 Jul 2022 11:38:23am
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "constants.h"

class squareInfoComponent : public juce::Component
{
public:
    squareInfoComponent()
    {
        setSize(200, 100);
    }

    ~squareInfoComponent() override {}

    void paint (juce::Graphics& g) override
    {
        g.setColour(juce::Colours::white);

        g.drawMultiLineText(
            juce::String(square_info.x) + "; " +
            juce::String(square_info.y) + '\n' +
            juce::String(square_info.road)  + '\n' +
            juce::String(square_info.depot),
                            0,
                            16,
                            200,
                            juce::Justification::left,
                            1.0f
        );

        repaint();
    }

    void resized() override
    {

    }


private:

};
