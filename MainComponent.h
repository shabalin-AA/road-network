#pragma once

#include <JuceHeader.h>
#include "map.h"


class MainComponent  : public juce::Component,
                       public juce::TextButton::Listener
{
public:
    MainComponent()
    {
        setSize (mapWidth - mapWidth % squareSize + frame * 2,
                 mapHeight - mapHeight % squareSize + frame * 2);
        addAndMakeVisible(M);

        addAndMakeVisible(clearButton);
        clearButton.addListener(this);

        addAndMakeVisible(saveButton);
        saveButton.addListener(this);

        addAndMakeVisible(loadButton);
        loadButton.addListener(this);

        addAndMakeVisible(carButton);
        carButton.addListener(this);
    }

    ~MainComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        //
    }

    void resized() override
    {
        M.setBounds(frame, frame,  mapWidth, mapHeight);

        clearButton.setBounds(0 * squareSize, 0, 2 * squareSize, frame);
        saveButton.setBounds (2 * squareSize, 0, 2 * squareSize, frame);
        loadButton.setBounds (4 * squareSize, 0, 2 * squareSize, frame);
        carButton.setBounds  (6 * squareSize, 0, 2 * squareSize, frame);
    }



    juce::TextButton saveButton  {"save"};
    juce::TextButton loadButton  {"load"};
    juce::TextButton clearButton {"clear"};
    juce::TextButton carButton   {"car"};

    void buttonClicked (juce::Button* b)
    {
        if (b == &saveButton)
            M.save();
        if (b == &loadButton)
            M.load();
        if (b == &clearButton)
            M.clear();
        if (b == &carButton)
            M.addCar();
    }



private:
    map M;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
