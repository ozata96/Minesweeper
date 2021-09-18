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
    void SetBoard();
    void LoadBoard();
    vector<string> SetInitialBoard(vector<string> map);
    bool CheckCoordinate(string coordinate, vector<string> dangerCoords);
    void PrintBoard(vector<string> map);
    void UncoverBlock(vector<string> &map, string coordinate, vector<string> dangerCoords);

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