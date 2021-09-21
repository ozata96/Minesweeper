#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <sstream>
#include "minesweeper.hpp"

using namespace std;

/*
     ABCDEFGHIJKLMNOPQR
    +------------------+
   A|??????????????????|
   B|??????????????????|
   C|??????????????????|
   D|??????????????????|
   E|??????????????????|
   F|??????????????????|
   G|??????????????????|
   H|??????????????????|
   I|??????????????????|
    +------------------+
*/
int getNumber(char input)
{
    switch (input)
    {
    case 'A':
        return 2;
    case 'B':
        return 3;
    case 'C':
        return 4;
    case 'D':
        return 5;
    case 'E':
        return 6;
    case 'F':
        return 7;
    case 'G':
        return 8;
    case 'H':
        return 9;
    case 'I':
        return 10;
    case 'J':
        return 11;
    case 'K':
        return 12;
    case 'L':
        return 13;
    case 'M':
        return 14;
    case 'N':
        return 15;
    case 'O':
        return 16;
    case 'P':
        return 17;
    case 'Q':
        return 18;
    case 'R':
        return 19;
    default:
        return 0;
    }
}

void givePositions(string position, int &row, int &col)
{
    row = getNumber(position[0]);
    col = getNumber(position[1]);
}

void Minesweeper::UncoverBlock(vector<string> &map, string coordinate, vector<string> dangerCoords)
{
    map[static_cast<int>(coordinate[0] - 48)][static_cast<int>(coordinate[1] - 48)] = '!';
}

int Minesweeper::countMines(string position, vector<string> dangerMap)
{
    int row, col;
    givePositions(position, row, col);

    int mineCount = 0;
    int rowStart = row - 3;
    int colStart = col - 3;

    cout << rowStart << endl;
    cout << colStart << endl;
    
    for (int i = rowStart; i < (rowStart + 3); i++){
        for (int j = colStart; j < (colStart + 3); j++){
            if (dangerMap[i][j] == '*')
                mineCount++;
        }
    }
    return mineCount;
}

bool Minesweeper::isComplete(vector<string> map)
{
    for (int i = 0; i < map.size(); i++)
        for (int j = 0; j < map[0].size(); j++)
            if (map[i][j] != '*')
                if (map[i][j] == '?')
                    return false;
    return false;
}

char Minesweeper::Printchar(int row)
{
    char output;

    switch (row)
    {
    case 0:
        return 'A';
    case 1:
        return 'B';
    case 2:
        return 'C';
    case 3:
        return 'D';
    case 4:
        return 'E';
    case 5:
        return 'F';
    case 6:
        return 'G';
    case 7:
        return 'H';
    case 8:
        return 'I';
    default:
        return 'X';
    }
}

vector<string> Minesweeper::SetInitialBoard(vector<string> map)
{
    vector<string> board;
    string line = "  ABCDEFGHIJKLMNOPQR ";
    board.push_back(line);
    line = "";

    for (int i = 0; i <= map[0].size() + 1; i++)
    {
        if (i == 0)
        {
            line.push_back(' ');
            line.push_back('+');
        }
        else if (i == map[0].size() + 1)
            line.push_back('+');
        else
            line.push_back('-');
    }
    board.push_back(line);

    for (int row = 0; row < map.size(); row++)
    {
        line = "";
        for (int col = 0; col <= map[0].size(); col++)
        {
            if (col == 0)
            {
                line.push_back(Printchar(row));
                line.push_back('|');
            }
            if (col == map[0].size())
                line.push_back('|');
            else
            {
                line.push_back('?');
            }
        }
        board.push_back(line);
    }
    line = " ";

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

MoveResult Minesweeper::make_move(std::string position, vector<string> mines, vector<string> &revealed)
{
    // Setup
    int row = 0;
    int col = 0;

    // Checks

    givePositions(position, row, col);

    if (row < 2 || row > 10)
        return INVALID_MOVE;
    if (col < 2 || col > 24)
        return INVALID_MOVE;

    if (revealed[row][col] != '?')
        return REDUNDANT_MOVE;

    if (mines[row - 2][col - 2] == '*')
        return BLOWN_UP;

    // if the move is valid and we want to flag
    if (position.length() == 3)
    { // move here is to flag not reveal
        if (position[2] != '*')
            return INVALID_MOVE;
        revealed[row][col] = '*';
        return VALID_MOVE;
    }

    // if the move is valid and we want to reveal
    int num_of_mines = countMines(position, mines);

    if (num_of_mines != 0)
    {
        char num_mines_char = num_of_mines + 48;
        revealed[row][col] = num_mines_char;
        return VALID_MOVE;
    }
    revealed[row][col] = ' ';

    std::string tempPosition = position;

    // RECURSIVE FLOOD

    //CHECK TL:
    tempPosition[0] = tempPosition[0] - 1;
    tempPosition[1] = tempPosition[1] - 1;
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK TT:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] - 1;
    tempPosition[1] = tempPosition[1];
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK TR:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] - 1;
    tempPosition[1] = tempPosition[1] + 1;
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK BL:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] + 1;
    tempPosition[1] = tempPosition[1] - 1;
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK BB:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] + 1;
    tempPosition[1] = tempPosition[1];
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK BR:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] + 1;
    tempPosition[1] = tempPosition[1] + 1;
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK RR:
    tempPosition = position;
    tempPosition[0] = tempPosition[0];
    tempPosition[1] = tempPosition[1] + 1;
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK LL:
    tempPosition = position;
    tempPosition[0] = tempPosition[0];
    tempPosition[1] = tempPosition[1] - 1;
    make_move(tempPosition, mines, revealed);
    //---------------------------------------//
    return VALID_MOVE;

    /*   0    1    2    3    4    5
          +----+----+----+----+----+----+               board[row][col]
       0  |      TL   TT   TR                       TL:
          +----+----+----+----+----+----+           position[0] = row = +1
       1  |      LL        RR                       position[1] = col = -1
          +----+----+----+----+----+----+
       2  |      BL   BB   BR
          +----+----+----+----+----+----+
    
       BASE: [1][2] - B3
                                    
         TL: [0][1] - A2
         TT: [0][2] - A3
         TR: [0][3] - A4
    
         BL: [2][1] - C2
         BB: [2][2] - C3
         BR: [2][3] - C4
         
         LL: [1][1] - B2
         RR: [1][3] - B4
    */
    // top, down, left, right
    // topleft, topright, bottomleft, bottomright
}
