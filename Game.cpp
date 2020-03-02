//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 390, Assignment 1

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

#include "Game.h"

Game::Game() { }

Game::~Game() { }

bool Game::createBoard(string filename)
{
    ifstream boardFile;
    boardFile.open(filename.c_str());

    bool firstLine = true; // the first line is the board size so that needs to be treated differently

    string str; //read from input file
    int lineCounter = 0;
    int charCounter = 0;
    currStepCounter = 0;

    try {
      if(boardFile.is_open())
      {
        while(!boardFile.eof())
        {
          getline(boardFile, str);

          if(firstLine)
          {
            boardSize = stoi(str);

            board = new Square*[boardSize]();
            for(int i = 0; i < boardSize; i++)
            {
              board[i] = new Square[boardSize]();
              for(int j = 0; j < boardSize; j++)
              {
                board[i][j] = Square();
              }
            }

            firstLine = false;
            continue;
          } // the first line is the board size. After you get this create the board and continue.

          for(int charCounter = 0; charCounter < str.length(); charCounter++)
          {
            char typeChar = str.at(charCounter); // getting the type, obstacle vs path vs initial or goal, of each square
            int type = 0;
            if(typeChar == '.')
              type = 1;
            else if(typeChar == '+')
              type = 2;
            else if(typeChar == 'i')
            {
              type = 3;
              initialRow = lineCounter;
              initialCol = charCounter;
            }
            else if(typeChar == 'g')
            {
              type = 4;
              goalRow = lineCounter;
              goalCol = charCounter;
            }

            board[lineCounter][charCounter].setRow(lineCounter);
            board[lineCounter][charCounter].setCol(charCounter);
            board[lineCounter][charCounter].setType(type);

            if(type == 3)
            {
              board[lineCounter][charCounter].setVisted(true);
              board[lineCounter][charCounter].setPathCost(-1);
              pathVec.push_back(&board[lineCounter][charCounter]);
            } // insert pointer to the intial state as the start of the path vector
          }

          lineCounter++;
        }

        boardFile.close();
      }
    } catch(exception e)
    {
      cout << "There was an error reading in the board." << endl;
      return false;
    }

    return true; // if the program successfully ran then return true
}

bool Game::assignPathCost(int searchAlgoInput)
{
    searchAlgo = searchAlgoInput;

    if(searchAlgo == 1 || searchAlgo == 3) // Euclidean distance or A* with Euclidean distance
      return euclideanCost();
    else // Manhattan distance or A* with Manhattan distance
      return manhattanCost();
}

bool Game::euclideanCost()
{
  //  E((i,j),(i',j')) = sqrt[(i-i')^2+(j-j')^2]
  try
  {
    for(int row = 0; row < boardSize; row++)
    {
      for(int col = 0; col < boardSize; col++)
      {
        int term1 = (col - goalCol);
        int term2 = (row - goalRow);
        int cost = sqrt((term1 * term1) + (term2 * term2));
        board[row][col].setPathCost(cost);
      }
    }

    return true; // if nothing went wrong, we return true.
  }
  catch(exception e)
  {
    return false;
  }
}

bool Game::manhattanCost()
{
  // M((i,j),(i',j')) = |i-i'| + |j-j'|
  try
  {
    for(int row = 0; row < boardSize; row++)
    {
      for(int col = 0; col < boardSize; col++)
      {
        int cost = abs(col - goalCol) + abs(row - goalRow);
        board[row][col].setPathCost(cost);
      }
    }

    return true; // if nothing went wrong, we return true.
  }
  catch(exception e)
  {
    return false;
  }
}

void Game::findPath()
{
  Square* initialNode = new Square();
  initialNode->setRow(initialRow);
  initialNode->setCol(initialCol);

  if(searchAlgo == 3 || searchAlgo == 4)
  {
    vector<Square*> allPossibleSteps = vector<Square*>();
    if(findAStarPath(initialNode, allPossibleSteps))
    {
      cout << "" << endl;
      printMap();
      cout << "\nThe Total Path Cost is: " << totalPathCost << endl;
    }
  }
  else
  {
    if(findRegularPath(initialNode))
    {
      cout << "" << endl;
      printMap();
      cout << "\nThe Total Path Cost is: " << totalPathCost << endl;
    }
  }
}

bool Game::findRegularPath(Square* currentNode)
{
  int currRow = currentNode->getRow();
  int currCol = currentNode->getCol();

  vector<Square*> possibleNextStep = findNextSquare(currRow, currCol);

  // Vector Sort Method from: https://www.geeksforgeeks.org/sorting-a-vector-in-c/
  sort(possibleNextStep.begin(), possibleNextStep.end(), compareRegSort);

  int frontRow = possibleNextStep.front()->getRow();
  int frontCol = possibleNextStep.front()->getCol();
  board[frontRow][frontCol].setOnPath(true);
  board[frontRow][frontCol].setVisted(true);

  totalPathCost = totalPathCost + possibleNextStep.front()->getPathCost();

  if(possibleNextStep.front()->getType() == 4)
  {
    return true; // goal is found!
  }

  return findRegularPath(possibleNextStep.front());
}

bool Game::findAStarPath(Square* currentNode, vector<Square*> allPossibleSteps)
{cout << "hi" << endl;
  int currRow = currentNode->getRow();
  int currCol = currentNode->getCol();

  vector<Square*> possibleNextStep = findNextSquare(currRow, currCol);

  auto it = possibleNextStep.begin();
  while(it != possibleNextStep.end())
  {cout << "hi2" << endl;
    Square* temp = *it;
    int row = temp->getRow();
    int col = temp->getCol();
    int cost = temp->getPathCost();

    board[row][col].setStepCost(currentNode->getStepCost() + 1);
    board[row][col].setTotalPathCost(currentNode->getStepCost() + cost + 1);
    board[row][col].setPreviousSquare(&board[currRow][currCol]);
    allPossibleSteps.push_back(temp);

    ++it;
  }

  // Vector Sort Method from: https://www.geeksforgeeks.org/sorting-a-vector-in-c/
  sort(allPossibleSteps.begin(), allPossibleSteps.end(), compareAStarSort);
  // This will sort the smallest at the back
cout << "hi3" << endl;
  int frontRow = allPossibleSteps.front()->getRow();
  int frontCol = allPossibleSteps.front()->getCol();
  board[frontRow][frontCol].setVisted(true);
  board[frontRow][frontCol].setPathCost(board[frontRow][frontCol].getPreviousSquare()->getStepCost() + 1);

cout << "hi4" << endl;
  if(allPossibleSteps.back()->getType() == 4)
  {
    //trace path back
    Square* temp = allPossibleSteps.back();
    for(int i = 0; i < temp->getStepCost(); i++)
    {
      int row = temp->getRow();
      int col = temp->getCol();

      board[row][col].setOnPath(true);

      temp = temp->getPreviousSquare();
    }

    return true; // goal is found!
  }

  Square* temp = allPossibleSteps.back();
  allPossibleSteps.pop_back();
  return findAStarPath(temp, allPossibleSteps);
}

vector<Square*> Game::findNextSquare(int currRow, int currCol)
{
  vector<Square*> possibleNextStep = vector<Square*>();

  // find next Square
  if(currCol == 0) // if start is in the far left column
  {
    if(currRow == 0) // if also in the top row
    {
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
    }
    else if(currRow == (boardSize - 1)) // if also in bottom row
    {
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
    else
    {
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
  }
  else if(currCol == (boardSize - 1)) // if start is in the far right column
  {
    if(currRow == 0) // if also in the top row
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
    }
    else if(currRow == (boardSize - 1)) // if also in bottom row
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
    else
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
  }
  else if(currRow == 0) // in top row
  {
    if(currCol == 0) // and far left column
    {
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
    }
    else if(currCol == (boardSize - 1)) // and far right column
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
    }
    else
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow + 1][currCol]);
    }
  }
  else if(currRow == (boardSize - 1)) // in bottom row
  {
    if(currCol == 0) // and far left column
    {
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
    else if(currCol == (boardSize - 1)) // and far right column
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
    else
    {
      possibleNextStep.push_back(&board[currRow][currCol - 1]);
      possibleNextStep.push_back(&board[currRow][currCol + 1]);
      possibleNextStep.push_back(&board[currRow - 1][currCol]);
    }
  }
  else // not on an edge
  {
    possibleNextStep.push_back(&board[currRow][currCol - 1]);
    possibleNextStep.push_back(&board[currRow][currCol + 1]);
    possibleNextStep.push_back(&board[currRow + 1][currCol]);
    possibleNextStep.push_back(&board[currRow - 1][currCol]);
  }

  bool foundGoal = false;

  // Remove element inside loop information from https://www.techiedelight.com/remove-elements-vector-inside-loop-cpp/
  auto it = possibleNextStep.begin();
  while(it != possibleNextStep.end())
  {
    Square* temp = *it;

    if(temp->getVisted()) // if it's been visited remove it from the vector
    {
      possibleNextStep.erase(it);
    }
    else if(temp->getType() == 2) // if it's an obstacle remove it from the vector
    {
      possibleNextStep.erase(it);
    }
    else
    {
      ++it;
    }
  }

  return possibleNextStep;
}

bool Game::compareRegSort(Square* sq1, Square* sq2) {
  return (sq1->getPathCost() < sq2->getPathCost());
}

bool Game::compareAStarSort(Square* sq1, Square* sq2) {
  return (sq1->getTotalPathCost() < sq2->getTotalPathCost());
}

bool Game::printMap()
{
  try
  {
    for(int row = 0; row < boardSize; row++)
    {
      string line = "";
      for(int col = 0; col < boardSize; col++)
      {
        line = line + board[row][col].mapChar();
      }
      cout << line << endl;
    }

    return true;
  }
  catch(exception e)
  {
    cout << "There was an error printing the map." << endl;
    return false;
  }
}
