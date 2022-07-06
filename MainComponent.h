#pragma once

#include <JuceHeader.h>
#include "map.h"
#include "squareInfo.h"



class MainComponent  : public juce::Component,
                       public juce::TextButton::Listener
{
public:
    MainComponent()
    {
        setSize (width + 100, height + 100);

        addAndMakeVisible(square_info_component);

        addAndMakeVisible(buildDepotButton);
        buildDepotButton.addListener(this);

        addAndMakeVisible(clearButton);
        clearButton.addListener(this);

        addAndMakeVisible(clearAllButton);
        clearAllButton.addListener(this);

        addAndMakeVisible(findPathButton);
        findPathButton.addListener(this);

        addAndMakeVisible(saveButton);
        saveButton.addListener(this);

        addAndMakeVisible(loadButton);
        loadButton.addListener(this);

        addChildComponent(map);
        addAndMakeVisible(map);
    }

    ~MainComponent() override {}

    void paint (juce::Graphics& g) override
    {
        map.checkSelected();
    }

    void resized() override
    {
        map.setBounds(0, 0, width, height);

        square_info_component.setBounds(0, height, 200, 100);

        int buttonHeight = 30;
        buildDepotButton.setBounds(width, 0,              100, buttonHeight);
        clearButton.setBounds     (width, 1*buttonHeight, 100, buttonHeight);
        clearAllButton.setBounds  (width, 2*buttonHeight, 100, buttonHeight);
        findPathButton.setBounds  (width, 3*buttonHeight, 100, buttonHeight);
        saveButton.setBounds      (width, 4*buttonHeight, 100, buttonHeight);
        loadButton.setBounds      (width, 5*buttonHeight, 100, buttonHeight);
    }

    void mouseDown (const juce::MouseEvent& event) override
    {
        globalEvent = globalEvents::globalNoEvent;
        repaint();
    }

    void buttonClicked (juce::Button* b)
    {
        if (b == &buildDepotButton)
        {
            if (globalEvent == buildDepot)
                globalEvent = globalNoEvent;
            else
                globalEvent = buildDepot;
        }

        if (b == &clearAllButton)
            globalEvent = globalEvents::globalClear;

        if (b == &clearButton)
            globalEvent = globalEvents::clear;

        if (b == &findPathButton)
        {
            if (globalEvent == globalEvents::findPath)
                globalEvent = globalEvents::savePath;
            else
                globalEvent = globalEvents::findPath;
        }

        if (b == &saveButton)
            globalEvent = globalEvents::save;

        if (b == &loadButton)
            globalEvent = globalEvents::load;
    }


private:
    Map map;

    squareInfoComponent square_info_component;

    juce::TextButton buildDepotButton {"biuld depot"};
    juce::TextButton clearButton      {"clear"};
    juce::TextButton clearAllButton   {"clear all"};
    juce::TextButton findPathButton   {"find path"};
    juce::TextButton saveButton       {"save"};
    juce::TextButton loadButton       {"load"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
