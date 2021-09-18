#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <sstream>
#include "minesweeper.hpp"

using namespace std;

void Minesweeper::UncoverBlock(vector<string> &map, string coordinate, vector<string> dangerCoords)
{
    map[static_cast<int>(coordinate[0] - 48)][static_cast<int>(coordinate[1] - 48)] = '!';



}

vector<string> Minesweeper::SetInitialBoard(vector<string> map)
{
    vector<string> board;
    string line = "";

    for (int i = 0; i <= map[0].size() + 1; i++)
    {
        if (i == 0 || (i == map[0].size() + 1))
            line.push_back('+');
        else
            line.push_back('-');
    }
    board.push_back(line);


    for (int row = 0; row < map.size(); row++)
    {
        line = "";
        for (int col = 0; col <= map[0].size() + 1; col++)
        {
            if (col == 0 || col == map[0].size() + 1)
            {
                line.push_back('|');
            }
            else
            {
                line.push_back('?');
            }
        }
        board.push_back(line);
    }
    line = "";

    for (int i = 0; i <= map[0].size() + 1; i++)
    {
        if (i == 0 || (i == map[0].size() + 1))
            line.push_back('+');
        else
            line.push_back('-');
    }
    board.push_back(line);

    return board;
};

void Minesweeper::PrintBoard(vector<string> board)
{
        for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}
