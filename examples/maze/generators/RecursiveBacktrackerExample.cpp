#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <algorithm>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  auto sideOverTwo = w->GetSize() / 2;
  if (stack.empty() && !visited[-sideOverTwo][-sideOverTwo])
  {
    stack.emplace_back(-sideOverTwo, -sideOverTwo);

    return true;
  }

  std::cout << stack.front().x << stack.front().y << std::endl;

   std::vector<Point2D> visitables = getVisitables(w, randomStartPoint(w));
   w->SetNodeColor(visitables[0],Color::Red); 



    return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this

  //Bool fors up right down left
  bool UP, RIGHT, DOWN, LEFT;
  int totalAvailable = 0;
  UP = w->GetSouth(p);
  RIGHT = w->GetEast(p);
  DOWN = w->GetNorth(p);
  LEFT = w->GetWest(p);


    if (UP)
    if (!visited[p.Up().x][p.Up().y] && !vectorContains(p.Up(), stack)) {
            visitables.push_back(p.Up());
            totalAvailable++;
          }
        
    if (RIGHT)
      if (!visited[p.Right().x][p.Right().y] && !vectorContains(p.Right(), stack)) {
            visitables.push_back(p.Right());
            totalAvailable++;
          }
          
    if (DOWN)
      if (!visited[p.Down().x][p.Down().y] && !vectorContains(p.Down(), stack)) {
            visitables.push_back(p.Down());
            totalAvailable++;
         }
         
    if (LEFT)
        if (!visited[p.Left().x][p.Left().y] && !vectorContains(p.Left(), stack)) {
            visitables.push_back(p.Left());
            totalAvailable++;
            }
          

    for (int i = 0; i < totalAvailable; i++)
    {
      std::cout << visitables[i].x << " " << visitables[i].y << std::endl;
    }

  return visitables;
}
