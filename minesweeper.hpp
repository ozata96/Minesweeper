#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <sstream>

using namespace std;

enum MoveResult { INVALID_MOVE=-3, REDUNDANT_MOVE=-2, BLOWN_UP=-1, SOLVED_BOARD=1, VALID_MOVE=0 };

class Minesweeper
{
public:
    void setBoard();
    void loadBoard();
    vector<string> setInitialBoard(vector<string> map, char selection);
    int getNumber(char input);
    void givePositions(string position, int &row, int &col);
    
    bool checkInput(string input);
    bool isComplete(vector<string> map, vector<string> mines);
    int countMines(string position, vector<string> dangerMap);
    MoveResult makeMove(std::string position, vector<string> mines, vector<string> &revealed);
    char printChar(int row);
    void printBoard(vector<string> map);
    void uncoverBlock(vector<string> &map, string coordinate, vector<string> dangerCoords);

private:


    /* 
          123456789
         +---------+
        A|?????????|
        B|?????????|
        C|?????????|
        D|?????????|
        E|?????????|
        F|?????????|
        G|?????????|
        H|?????????|
        I|?????????|
         +---------+
    */








};