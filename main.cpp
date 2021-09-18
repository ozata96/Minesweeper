#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <sstream>
#include "minesweeper.hpp"

using namespace std;


int main ()
{
        string coordinate = "";

    Minesweeper control;
    string coord = "";
    char x, y;

    ifstream file("TestMines.txt");
    vector<string> dangerMap;
    vector<string> newMap;

    string input;
    while (file >> input)
    {
        dangerMap.push_back(input);
    }

    vector<string> dangerCoords;

    for (int i = 0; i < dangerMap[0].size(); i++)
    {
        for (int j = 0; j < dangerMap.size(); j++)
        {
            if (dangerMap[i][j] == '*')
            {
                x = static_cast<char>(i) + 48;
                y = static_cast<char>(j) + 48;

                cout << x << y << endl;
                coord.push_back(x);
                coord.push_back(y);
                dangerCoords.push_back(coord);
                coord = "";
            }
        }
    }
    control.PrintBoard(dangerMap);

    newMap = control.SetInitialBoard(dangerMap);
    control.PrintBoard(newMap);
    // for (int i = 0; i < dangerCoords.size(); i++)
    // {
    //     cout << dangerCoords[i] << endl;
    // }

    cin >> coordinate;

    control.CheckCoordinate(coordinate, dangerCoords);

    control.UncoverBlock(newMap, coordinate, dangerCoords);
    control.PrintBoard(newMap);
}