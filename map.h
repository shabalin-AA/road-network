/*
  ==============================================================================

    map.h
    Created: 30 Jun 2022 6:56:09pm
    Author:  l

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "square.h"
#include <fstream>
#include <vector>
#include <cmath>

std::string path_file_name;
std::string map_file = "savings/map_save.txt";



class Map : public juce::Component
{
public:
    Map()
    {
        setSize (width, height);

        for (int i = 0; i < width / squareSize + 2; i++)
            for (int j = 0; j < height / squareSize + 2; j++)
            {
                addChildComponent(map[i][j]);
                addAndMakeVisible(map[i][j]);
            }
    }

    ~Map() override {}

    void paint (juce::Graphics& g) override
    {
        if (globalEvent == globalEvents::globalClear)
        {
            for (int i = 0; i < width / squareSize + 2; i++)
                for (int j = 0; j < height / squareSize + 2; j++)
                {
                    map[i][j].road = false;
                    map[i][j].depot = false;
                }

            globalEvent = globalEvents::globalNoEvent;
        }



        if (globalEvent == globalEvents::save)
        {
            std::ofstream map_save(map_file);

            for (int i = 0; i < width / squareSize + 2; i++)
            {
                for (int j = 0; j < height / squareSize + 2; j++)
                {
                    if (map[i][j].depot)
                        map_save << 'd';
                    else if (map[i][j].road)
                        map_save << 'r';
                    else
                        map_save << 'e';
                }

                map_save << '\n';
            }

            map_save.close();
        }



        if (globalEvent == globalEvents::load)
        {
            std::ifstream map_load(map_file);
            std::string str;

            for (int i = 0; getline(map_load, str); i++)
            {
                for (int j = 0; j < str.length(); j++)
                {
                    if (str[j] == 'e')
                    {
                        map[i][j].road = false;
                        map[i][j].depot = false;
                    }
                    else if (str[j] == 'r')
                    {
                        map[i][j].road = true;
                        map[i][j].depot = false;
                    }
                    else if (str[j] == 'd')
                    {
                        map[i][j].road = true;
                        map[i][j].depot = true;
                    }
                }
            }

            map_load.close();
        }
    }

    void resized() override
    {
        for (int i = 0; i < width / squareSize + 2; i++)
            for (int j = 0; j < height / squareSize + 2; j++)
            {
                map[i][j].X = i * squareSize;
                map[i][j].Y = j * squareSize;

                map[i][j].setBounds(
                    map[i][j].X - squareSize, map[i][j].Y - squareSize,
                    squareSize, squareSize);
            }
    }

    void checkSelected()
    {
        for (int i = 0; i < width / squareSize + 2; i++)
            for (int j = 0; j < height / squareSize + 2; j++)
            {
                if (!map[i][j].road)
                    map[i][j].selectedForPath = false;

                if (map[i][j].selected)
                {
                    square_info.x = i /*map[i][j].X / squareSize*/;
                    square_info.y = j /*map[i][j].Y / squareSize*/;

                    if (map[i][j].road)
                        square_info.road = "road";
                    else
                        square_info.road = "no road";

                    if (map[i][j].depot)
                        square_info.depot = "depot";
                    else
                        square_info.depot = "no depot";
                }

                if (globalEvent == globalEvents::savePath)
                {
                    std::ofstream fout(
                        "savings/path_" +
                        std::to_string(path_counter) +
                        ".txt"
                    );
                    path_counter++;

                    if (route_counter > 1)
                        for (int i = 0; i + 1 < route_counter; i++)
                            pathFinding(route[i], route[i+1], fout);

                    fout.close();

                    globalEvent = globalEvents::globalNoEvent;
                    route.erase(route.begin(), route.begin() + route_counter);
                    route_counter = 0;
                }

                if (map[i][j].selectedForPath)
                {
                    if (checkRoute(i, j))
                    {
                        squareInfo square_for_path;
                        square_for_path.x = i;
                        square_for_path.y = j;

                        route.push_back(square_for_path);
                        route_counter++;
                    }
                }
            }
    }

    bool checkRoute (int x, int y)
    {
        for (int i = 0; i < route_counter; i++)
            if (route[i].x == x && route[i].y == y)
                return false;

        return true;
    }

    void clearSelectedForPath ()
    {
        for (int i = 0; i < width / squareSize + 2; i++)
            for (int j = 0; j < height / squareSize + 2; j++)
                map[i][j].selectedForPath = false;
    }

    void pathFinding (squareInfo b, squareInfo e, std::ofstream& fout)
    {
        clearSelectedForPath();

        std::ofstream log("savings/log.txt");
        log << "b:" << b.x << ' ' << b.y << '\n';
        log << "e:" << e.x << ' ' << e.y << '\n';

        int max_iter = 0;
        while (!(b.x == e.x && b.y == e.y) &&
               max_iter < width * height)
        {
            map[b.x][b.y].selectedForPath = true;

            fout << b.x << ' ' << b.y << '\n';



            squareInfo left;
                left.x = b.x - 1;
                left.y = b.y;
                left.euristic = (abs(e.x - left.x) + abs(e.y - left.y));

            squareInfo right;
                right.x = b.x + 1;
                right.y = b.y;
                right.euristic = (abs(e.x - right.x) + abs(e.y - right.y));

            squareInfo up;
                up.x = b.x;
                up.y = b.y - 1;
                up.euristic = (abs(e.x - up.x) + abs(e.y - up.y));

            squareInfo down;
                down.x = b.x;
                down.y = b.y + 1;
                down.euristic = (abs(e.x - down.x) + abs(e.y - down.y));


            std::vector <squareInfo> find_min; int vect_size = 0;
            if (map[left.x][left.y].road &&
                !map[left.x][left.y].selectedForPath)
            {
                find_min.push_back(left); vect_size++;
                log << "left" << ' ';
            }

            if (map[right.x][right.y].road &&
                !map[right.x][right.y].selectedForPath)
            {
                find_min.push_back(right); vect_size++;
                log << "right" << ' ';
            }

            if (map[up.x][up.y].road &&
                !map[up.x][up.y].selectedForPath)
            {
                find_min.push_back(up); vect_size++;
                log << "up" << ' ';
            }

            if (map[down.x][down.y].road &&
                !map[down.x][down.y].selectedForPath)
            {
                find_min.push_back(down); vect_size++;
                log << "down" << ' ';
            }



            squareInfo min; min.euristic = 100;
            for (int i = 0; i < vect_size; i++)
            {
                if (find_min[i].euristic <= min.euristic)
                {
                    min.x = find_min[i].x;
                    min.y = find_min[i].y;
                    min.euristic = find_min[i].euristic;

                    log << '\n' << "min:" << min.x << ' ' << min.y << ' ' << min.euristic << '\n';
                }
            }

            find_min.erase(find_min.begin(), find_min.begin() + vect_size);
            vect_size = 0;

            b.x = min.x;
            b.y = min.y;
            max_iter++;
        }

        fout << e.x << ' ' << e.y << '\n';

        clearSelectedForPath();
    }


private:
    square map[width / squareSize + 2][height / squareSize + 2];

    std::vector <squareInfo> route; int route_counter = 0;
};
