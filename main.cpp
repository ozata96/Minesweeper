#include <iostream>
#include <fstream>
// #include <cstdio>
#include <cstring>
// #include <cassert>
#include <vector>
#include <sstream>
#include "minesweeper.hpp"

using namespace std;

void loadLevel(string levelName, vector<string> &outputMap)
{
    ifstream file(levelName);

    string input;
    while (file >> input)
    {
        outputMap.push_back(input);
    }
}

void selectLevel(char selection, vector<string> &outputMap)
{
    switch (selection)
    {
    case '0':
        loadLevel("Easy.txt", outputMap);
        break;
    case '1':
        loadLevel("Medium.txt", outputMap);
        break;
    case '2':
        loadLevel("Hard.txt", outputMap);
        break;
    case '3':
        exit(0);
    default:
        cout << "Invalid input" << endl;
    }
}

void ClearScreen()
{
    int n;
    for (n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}

int main()
{
    Minesweeper control;
    vector<string> map;
    vector<string> dangerMap;

    string input;

    while (input[0] != '3')
    {
        map.clear();
        dangerMap.clear();
        cout << "Please select a map to load:" << endl;
        cout << "EASY [0]    MEDIUM [1]    HARD [2]   EXIT [3]" << endl;

        cin >> input;

        if (input[0] != '0' && input[0] != '1' && input[0] != '2' && input[0] != '3')
            cerr << "Invalid input, please enter number between 0 and 3" << endl;
        else
        {
            selectLevel(input[0], dangerMap);

            map = control.setInitialBoard(dangerMap, input[0]);
            control.printBoard(map);

            string position = "";
            while (position != "MAIN")
            {
                cout << "Input Example: AA or CE, or FD" << endl;
                cout << "Type MAIN to return to main menu" << endl;
                cout << "Input: ";
                cin >> position;
                cout << endl;
                control.checkInput(position);

                switch (control.makeMove(position, dangerMap, map))
                {
                case -3:
                    cerr << "Invalid Move" << endl;
                    break;
                case -2:
                    cerr << "Redundant Move" << endl;
                    break;
                case -1:
                    cerr << "BOOM - You have chosen a mine." << endl;
                    position = "MAIN";
                    break;
                case 1:
                    cerr << "Congratulations, you have solved the board" << endl;
                    break;
                case 0:
                    ClearScreen();
                    control.printBoard(map);
                    // control.checkWin(map, dangerMap);
                    break;
                }


            }
        }
    }
}