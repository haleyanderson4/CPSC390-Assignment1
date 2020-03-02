//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 390, Assignment 1

#include "Square.h"

Square::Square() { } // blank constructor

Square::Square(int inputType) // overload constructor
{
  visited = false;
  type = inputType;
  localCost = 0;
  costUntilThisPoint = 0;
  pathStepCost = 0;

  if(type == 3)
    onPath = true;
  else
    onPath = false;

  //previousSquare = NULL;
}

Square::~Square()
{
  //previousSquare = NULL;
}

char Square::mapChar()
{
  if(type == 1)
  {
    if(onPath)
      return 'o';
    else
      return '.';
  }
  else if(type == 2)
  {
    return '+';
  }
  else if(type == 3)
  {
    return 'i';
  }
  else if(type == 4)
  {
    return 'g';
  }
  else
  {
    return 'e'; // e is for error
  }
}

void Square::setType(int t) {
  type = t;
}
int Square::getType() {
  return type;
}

void Square::setPathCost(int cost) {
  localCost = cost;
}
int Square::getPathCost() {
  return localCost;
}

void Square::setTotalPathCost(int cost) {
  costUntilThisPoint = cost;
}
int Square::getTotalPathCost() {
  return costUntilThisPoint;
}

int Square::getRow() {
  return row;
}
void Square::setRow(int r) {
  row = r;
}
int Square::getCol() {
  return column;
}
void Square::setCol(int c) {
  column = c;
}

bool Square::getVisted() {
  return visited;
}
void Square::setVisted(bool v) {
  visited = v;
}

bool Square::getOnPath() {
  return onPath;
}
void Square::setOnPath(bool on) {
  onPath = on;
}

int Square::getStepCost() {
  return pathStepCost;
}
void Square::setStepCost(int stepCost) {
  pathStepCost = stepCost;
}

Square* Square::getPreviousSquare() {
  return previousSquare;
}
void Square::setPreviousSquare(Square* square) {
  previousSquare = square;
}
