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
    int mineCount;
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
    cout << dangerMap[0].size() << endl;
    cout << dangerMap.size() << endl;

    for (int i = 0; i < dangerMap.size(); i++)
    {
        for (int j = 0; j < dangerMap[0].size(); j++)
        {
            if (dangerMap[i][j] == '*')
            {
                mineCount++;
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

    cout << mineCount << endl;
    // cin >> coordinate;

    // control.CheckCoordinate(coordinate, dangerCoords);

    control.UncoverBlock(newMap, coordinate, dangerCoords);
    control.PrintBoard(newMap);

    string position = "";
    while (position != "Exit")
    {
        cin >> position;
        control.make_move(position, dangerMap, newMap);
        control.PrintBoard(newMap);
        cout << position.length() << endl;
    }
}