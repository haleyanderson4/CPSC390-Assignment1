//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 390, Assignment 1

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Square.h"

class Game
{
  public:
    Game(); //blank constructor
    ~Game();

    bool createBoard(string filename);
    void findPath();
    bool assignPathCost(int searchAlgoInput);
    bool euclideanCost();
    bool manhattanCost();

    vector<Square*> findNextSquare(int currRow, int currCol);
    static bool compareRegSort(Square* sq1, Square* sq2);
    static bool compareAStarSort(Square* sq1, Square* sq2);

    bool findAStarPath(Square* currentNode, vector<Square*> allPossibleSteps);
    bool findRegularPath(Square* currentNode);

    bool printMap();

  private:
    string filename;
    Square** board;
    Square initialNode;
    vector<Square*> pathVec; //vector of pointers to the board square
    int goalRow;
    int goalCol;
    int initialRow;
    int initialCol;

    int boardSize;
    int totalPathCost;

    int searchAlgo;

    int currStepCounter;
};
