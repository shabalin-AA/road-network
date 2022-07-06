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
    savePath
};



const int width = 600, height = 400;
const int squareSize = 50;

int path_counter = 0;

float speed = 0.005;



struct squareInfo
{
    int x = 0, y = 0, wt = 1;
    double euristic = 0;

    bool selectedForPath = false;

    juce::String road = "", depot = "";
};

squareInfo square_info;
