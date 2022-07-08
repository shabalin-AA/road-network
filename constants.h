/*
  ==============================================================================

    constants.h
    Created: 30 Jun 2022 7:18:08pm
    Author:  l

  ==============================================================================
*/

#pragma once

int globalEvent = -1;
enum globalEvents
{
    globalNoEvent,
    buildDepot,
    globalClear,
    clear,
    findPath,
    save,
    load,
    savePath,
    createCar,
    start
};



const int width = 600, height = 400;
const int squareSize = 50;
const int carWidth = 0.7 * squareSize, carHeight = 0.4 * squareSize;

int path_counter = 1;

float speed = 5;



struct squareInfo
{
    int x = 0, y = 0, wt = 1;
    double euristic = 0;

    bool selectedForPath = false;

    juce::String road = "", depot = "";

    void operator= (const squareInfo& another)
    {
        this->x = another.x;
        this->y = another.y;
        this->euristic = another.euristic;
    }
};

squareInfo square_info;
