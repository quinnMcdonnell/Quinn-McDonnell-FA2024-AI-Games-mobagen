#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  auto sideOverTwo = w->GetSize() / 2;
  if (stack.empty() && !visited[-sideOverTwo][-sideOverTwo])
  {
    stack.emplace_back(-sideOverTwo, -sideOverTwo);

    return true;
  }

   std::vector<Point2D> visitables = getVisitables(w, randomStartPoint(w));
   int size = visitables.size();
   if (size == 1)
   {
     w->GetNodeColor(visitables[0]).Shade100();
     visited.emplace(visitables[0]);
   } else 
   {
     int random = std::rand() % 100;
     int random = random % size;
     
     //return neighbor that is visitables[random]
   }



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
  UP = w->GetNorth(p);
  RIGHT = w->GetEast(p);
  DOWN = w->GetSouth(p);
  LEFT = w->GetWest(p);

  std::cout << p.x << p.y << UP << RIGHT << DOWN << LEFT << std::endl;

  if (UP)
     visited.find(w->GetNorth(p));
  if (RIGHT)
     visited.find(w->GetEast(p));
  if (DOWN)
     visited.find(w->GetSouth(p));
  if (LEFT)
     visited.find(w->GetWest(p));

  

  return visitables;
}
