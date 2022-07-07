/*
  ==============================================================================

    squareInfo.h
    Created: 3 Jul 2022 11:38:23am
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <fstream>
#include "constants.h"

class Car : public juce::Component
{
public:
    int x = 0, y = 0;
    bool ready = false;



    Car()
    {
        setSize(carWidth, carHeight);
    }

    ~Car() override {}

    void paint (juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::yellow);

        if (ready)
            g.drawText("y", 0, 0,
                       carWidth,
                       carHeight,
                       juce::Justification::centred);
        else
            g.drawText("n", 0, 0,
                       carWidth,
                       carHeight,
                       juce::Justification::centred);
    }

    void resized() override
    {

    }



    squareInfo stringToPoint (std::string coords)
    {
        squareInfo p;

        std::string x_temp = "", y_temp = "";
        int i = 0;
        for (; coords[i] != ' '; i++);
        x_temp = coords.substr(0, i);

        int j = i;
        for (; coords[j] != '\0'; j++);
        y_temp = coords.substr(i + 1, j - i);

        p.x = std::stoi(x_temp);
        p.y = std::stoi(y_temp);

        return p;
    }

    void setPath (int pathNumber = 1)
    {
        std::ifstream fin("savings/path_" + std::to_string(pathNumber) + ".txt");

        if (fin.is_open())
        {
            std::string temp_point;
            while (getline(fin, temp_point))
            {
                squareInfo point = stringToPoint(temp_point);
                point.x = (point.x - 1) * squareSize;
                point.y = (point.y - 1) * squareSize;

                //x = point.x; y = point.y;

                car_path.push_back(point);
                car_path_counter++;
            }

            ready = true;
            x = car_path[0].x; y = car_path[0].y;
        }
    }

    void updCoords ()
    {
        if (position + 2 > car_path_counter)
            ready = false;

        if (x < car_path[position + 1].x)
            x += speed;
        if (x > car_path[position + 1].x)
            x -= speed;
        if (y < car_path[position + 1].y)
            y += speed;
        if (y > car_path[position + 1].y)
            y -= speed;

        if (x == car_path[position + 1].x && y == car_path[position + 1].y)
            position++;
    }



private:

    std::vector <squareInfo> car_path; int car_path_counter = 0;
    int position = 0;

};
