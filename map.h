/*
  ==============================================================================

    map.h
    Created: 8 Aug 2022 8:04:34am
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "square.h"
#include "car.h"
#include <fstream>



class map  : public juce::Component
{
public:
    map()
    {
        setSize (mapWidth, mapHeight);

        for (int i = 0; i < mapWidth / squareSize; i++)
        {
            for (int j = 0; j < mapHeight / squareSize; j++)
            {
                addAndMakeVisible(Map[i][j]);
                Map[i][j].setBounds(i * squareSize,
                                    j * squareSize,
                                    squareSize,
                                    squareSize);
            }
        }
    }

    ~map() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        if (carFlag)
            move();
    }

    void resized() override
    {
        car.setBounds(car.x, car.y, squareSize, squareSize);
    }



    void save ()
    {
        std::ofstream map_save(map_file);

        for (int i = 0; i < mapWidth / squareSize; i++)
        {
            for (int j = 0; j < mapHeight / squareSize; j++)
            {
                if (Map[i][j].depot)
                    map_save << 'd';
                else if (Map[i][j].road)
                    map_save << 'r';
                else
                    map_save << 'e';
            }
            map_save << '\n';
        }
        map_save.close();
    }

    void load ()
    {
        std::ifstream map_load(map_file);
        std::string str;

        for (int i = 0; getline(map_load, str); i++)
        {
            for (int j = 0; j < str.length(); j++)
            {
                if (str[j] == 'e')
                {
                    Map[i][j].road = false;
                    Map[i][j].depot = false;
                }
                else if (str[j] == 'r')
                {
                    Map[i][j].road = true;
                    Map[i][j].depot = false;
                }
                else if (str[j] == 'd')
                {
                    Map[i][j].road = true;
                    Map[i][j].depot = true;
                }
            }
        }

        map_load.close();
        repaint();
    }

    void clear ()
    {
        for (int i = 0; i < mapWidth / squareSize; i++)
        {
            for (int j = 0; j < mapHeight / squareSize; j++)
            {
                Map[i][j].road = false;
                Map[i][j].depot = false;
            }
        }
        repaint();
    }

    void move ()
    {
        car.x++;
        car.y++;
        resized();
    }

    void addCar ()
    {
        addAndMakeVisible(car);
        carFlag = true;
    }

private:
    square Map[mapWidth / squareSize][mapHeight / squareSize];
    Car car;
    bool carFlag = false;
};
