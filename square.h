/*
  ==============================================================================

    square.h
    Created: 30 Jun 2022 6:06:17pm
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "constants.h"



class square  : public juce::Component
{
public:
    int X = 0, Y = 0;

    bool road = false, depot = false;
    bool selected = false;
    bool selectedForPath = false;



    square ()
    {
        setSize (squareSize, squareSize);
    }

    square (const square& another)
    {
        this->X = another.X;
        this->Y = another.Y;
        this->road = another.road;
        this->depot = another.depot;
    }

    ~square () override {}

    void paint (juce::Graphics& g) override
    {
        if (selected || selectedForPath)
        {
            g.fillAll(juce::Colours::palegreen);

            juce::Rectangle<int> select(0, 0, squareSize, squareSize);
            g.setColour(juce::Colours::grey);
            g.drawRect(select, 2.0f);

            repaint();
        }
        else
        {
            g.fillAll(juce::Colours::palegreen);
            repaint();
        }



        if (road)
        {
            int border = squareSize * 0.1;
            juce::Rectangle<int> road(
                border,
                border,
                squareSize - 2*border,
                squareSize - 2*border);
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(road);
        }



        if (depot)
        {
            int border = squareSize * 0.1;
            juce::Rectangle<int> road(
                border,
                border,
                squareSize - 2*border,
                squareSize - 2*border);
            g.setColour(juce::Colours::brown);
            g.fillRect(road);
        }



        juce::Rectangle<int> frame(0, 0, squareSize, squareSize);
        g.setColour(juce::Colours::lightgrey);
        g.drawRect(frame, 1.0f);
    }

    void resized() override
    {

    }

    void mouseEnter (const juce::MouseEvent& event) override
    {
        selected = true;
    }

    void mouseExit (const juce::MouseEvent& event) override
    {
        selected = false;
    }

    void mouseDown (const juce::MouseEvent& event) override
    {
        if (globalEvent == globalEvents::findPath && depot)
            selectedForPath = !selectedForPath;

        if (globalEvent == globalEvents::buildDepot && !depot)
        {
            depot = true;
            globalEvent = globalEvents::globalNoEvent;
        }

        if (!road)
            road = true;

        if (globalEvent == globalEvents::clear)
        {
            depot = false;
            road = false;
        }
    }

    void operator= (square another)
    {
        this->X               = another.X;
        this->Y               = another.Y;
        this->road            = another.road;
        this->depot           = another.depot;
    }

    bool operator== (square& another)
    {
        if (this->X               == another.X &&
            this->Y               == another.Y &&
            this->road            == another.road &&
            this->depot           == another.depot
        )
            return true;
        else
            return false;
    }


private:
};
