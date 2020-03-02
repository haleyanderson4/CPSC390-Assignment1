//Haley Anderson, 2270112, ander427@mail.chapman.edu, CPSC 390, Assignment 1

class Square
{
  public:

    Square();
    Square(int inputType);
    ~Square();

    void setType(int t);
    int getType();
    char mapChar();

    void setPathCost(int cost);
    int getPathCost();

    void setTotalPathCost(int cost);
    int getTotalPathCost();

    int getRow();
    void setRow(int r);
    int getCol();
    void setCol(int c);

    bool getVisted();
    void setVisted(bool v);

    bool getOnPath();
    void setOnPath(bool on);

    int getStepCost();
    void setStepCost(int stepCost);

    Square* getPreviousSquare();
    void setPreviousSquare(Square* square);

  private:
    int row;
    int column;

    int localCost;
    int costUntilThisPoint;
    bool visited;

    int pathStepCost;

    int type; // 1 for open, 2 for obstacle, 3 for inital state, 4 for goal state
    bool onPath;

    Square* previousSquare;
};
