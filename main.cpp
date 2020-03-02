//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 390, Assignment 1

#include "Game.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
  cout << "Thank you for using Haley's Robotic Search Program!" << endl;

  Game *searchPath = new Game(); // create our game object

  //makes sure the user runs the code with a text file
  if(argc != 2)
  {
    cout << "You did not enter a file. Please enter a file." << endl;
    exit(0);
  } //quits if no file to supply map
  string filename = argv[1]; // input file name

  if(!searchPath->createBoard(filename))
  {
    cout << "Something went wrong with processing your file. Please check your file and try again." << endl;
    exit(0);
    /* If the createBoard function throws and error it will return false. This means the board was not successfully
    created and therefore it cannot run. */
  }

  int searchAlgo;
  while(true)
  {
    cout << "Which Search Algorithm would you like to use? '1' for Euclidean distance, '2' for Manhattan distance, '3' for A* with Euclidean and '4' for A* with Manhattan." << endl;
    cout << "Enter 5 to quit." << endl;
    /* Ask the user to supply which search alogirhtm they would like to use, or if they want to quit.
    In a loop so that if the user accidentally messes up their input they don't need to wait for board generation again. */
    try {
      cin >> searchAlgo;
      if(searchAlgo < 1 || searchAlgo > 5) // If the given is not 1-4 then it is invalid and must try again.
      {
        cout << "Please enter an input of 1, 2, 3, 4, or 5." << endl;
        continue;
      }
      if(searchAlgo == 5)
      {
        cout << "You have choosen to quit the program." << endl;
        cout << "Thank you for choosing Haley's Robotic Search Program. Have a great day!" << endl;
        exit(0);
      }
      break; // if it threw no errors and is between 1 and 3 then continue through the code.
    } catch(exception e) // Non integer inputs will be directed here.
    {
      cout << "You entered an invalid input. Please try again." << endl;
      continue;
    }
  }

  if(searchPath->assignPathCost(searchAlgo) == false)
  {
    cout << "Something went wrong with processing your map. Please try again." << endl;
    exit(0);
  }

  searchPath->findPath(); // This is the function where the work is done. We were given that a solution exists so no non success catch.
  searchPath->~Game();
  cout << "Thank you for choosing Haley's Robotic Search Program. Have a great day!" << endl;

  return 0;
}
