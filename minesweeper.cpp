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

bool Minesweeper::checkInput(string input)
{
    string rowLibrary = "ABCDEFGHI";
    string colLibrary = "ABCDEFGHIJKLMNOPQR";

    if (input.length() > 3 && input != "MAIN")
    {
        cerr << "Invalid input, please try again" << endl;
        return false;
    }

    if (input.length() == 3 && input[2] != '*')
    {
        cerr << "Invalid input, please try again" << endl;
        return false;
    }

    if (input.length() < 4)
    {
        for (int i = 0; i < rowLibrary.length(); i++)
        {
            if (input[0] == rowLibrary[i])
                for (int j = 0; j < colLibrary.length(); j++)
                {
                    if (input[1] == colLibrary[j])
                        if (input.length() == 2)
                            return true;
                        if (input.length() == 3 && input[2] == '*')
                            return true;
                }
        }

    }
    cerr << "Invalid input" << endl;
    return false;
}


int Minesweeper::getNumber(char input)
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

void Minesweeper::givePositions(string position, int &row, int &col)
{
    row = getNumber(position[0]);
    col = getNumber(position[1]);
}

int Minesweeper::countMines(string position, vector<string> dangerMap)
{
    int row, col;
    givePositions(position, row, col);

    int mineCount = 0;
    int rowStart = row - 3;
    int colStart = col - 3;

    // cout << rowStart << endl;
    // cout << colStart << endl;
    
    for (int i = rowStart; i < (rowStart + 3); i++){
        for (int j = colStart; j < (colStart + 3); j++){
            if (dangerMap[i][j] == '*')
                if (i >= 0 && j >= 0)
                    mineCount++;
        }
    }
    return mineCount;
}

char Minesweeper::printChar(int row)
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

vector<string> Minesweeper::setInitialBoard(vector<string> map, char selection)
{
    string line = "";
    vector<string> board;
    if (selection == '0')
        line = "  ABCDEFGHIJ ";

    else if (selection == '1')
        line = "  ABCDEFGHIJKLM ";

    else if (selection == '2')
        line = "  ABCDEFGHIJKLMNOPQR ";


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
                line.push_back(printChar(row));
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

void Minesweeper::printBoard(vector<string> board)
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

bool Minesweeper::isComplete(vector<string> map, vector<string> mines)
{
    for (int row = 0; row < mines[0].length(); row++)
        for (int col = 0; col < mines.size(); col++)
        {
            if (map[row + 2][col + 2] == '?')
                return false;
            if (map[row + 2][col + 2] == '*' && mines[row][col] != '*')
                return false;
            // if (mines[row - 2][col - 2] == '*')
        }
return true;
}

MoveResult Minesweeper::makeMove(std::string position, vector<string> mines, vector<string> &revealed)
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

    // if the move is valid and we want to flag
    if (position.length() == 3)
    { // move here is to flag not reveal
        if (position[2] != '*')
            return INVALID_MOVE;
        revealed[row][col] = '*';
        return VALID_MOVE;
    }

    if (mines[row - 2][col - 2] == '*')
        return BLOWN_UP;

    // if the move is valid and we want to reveal
    int num_of_mines = countMines(position, mines);

    isComplete(revealed, mines);

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
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK TT:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] - 1;
    tempPosition[1] = tempPosition[1];
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK TR:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] - 1;
    tempPosition[1] = tempPosition[1] + 1;
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK BL:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] + 1;
    tempPosition[1] = tempPosition[1] - 1;
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK BB:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] + 1;
    tempPosition[1] = tempPosition[1];
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK BR:
    tempPosition = position;
    tempPosition[0] = tempPosition[0] + 1;
    tempPosition[1] = tempPosition[1] + 1;
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK RR:
    tempPosition = position;
    tempPosition[0] = tempPosition[0];
    tempPosition[1] = tempPosition[1] + 1;
    makeMove(tempPosition, mines, revealed);
    //---------------------------------------//
    //CHECK LL:
    tempPosition = position;
    tempPosition[0] = tempPosition[0];
    tempPosition[1] = tempPosition[1] - 1;
    makeMove(tempPosition, mines, revealed);
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
