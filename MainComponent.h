#pragma once

#include <JuceHeader.h>
#include "map.h"

class MainComponent  : public juce::Component
{
public:
    MainComponent()
    {
        setSize (width + 40, height + 40);

        addChildComponent(m);
    }

    ~MainComponent() override
    {

    }

    void paint (juce::Graphics& g) override
    {

        addAndMakeVisible(m);
    }

    void resized() override
    {
        m.setBounds(20, 20, width, height);
    }


private:
    map m;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
