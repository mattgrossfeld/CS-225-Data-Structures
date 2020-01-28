/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <queue>
#include <map>

#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

class SquareMaze{

public:

   SquareMaze();
   void makeMaze(int width, int height);
   bool canTravel(int x, int y, int dir) const;
   void setWall(int x, int y, int dir, bool exists);
   vector<int> solveMaze();
   cs225::PNG * drawMaze() const;
   cs225::PNG * drawMazeWithSolution();

private:

  vector<bool> vertWalls;
  vector<bool> horWalls;
  int mazeWidth;
  int mazeHeight;


};

#endif
