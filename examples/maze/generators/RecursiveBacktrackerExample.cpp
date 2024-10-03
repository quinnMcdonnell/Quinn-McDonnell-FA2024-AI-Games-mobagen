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
    w->SetNodeColor({-sideOverTwo, -sideOverTwo}, Color::Red);
    return true;
  }

  if (!stack.empty()) {
      //Get Neighbor
    std::vector<Point2D> visitables = getVisitables(w, stack[stack.size() - 1]);

    if (visitables.empty())
    {
      stack.pop_back();
      w->SetNodeColor(stack[stack.size() - 1], Color::Black);
      return true;
    }

    int random = rand() % visitables.size();
    auto next = visitables[random];
    stack.push_back(next);
    visited[next.x][next.y] = true;
    
    // break the wall between current and next current - next delta for the wall
    

    //Change color
    w->SetNodeColor(next, Color::Red);

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
  UP = w->GetSouth(p);
  RIGHT = w->GetEast(p);
  DOWN = w->GetNorth(p);
  LEFT = w->GetWest(p);


    if (UP)
    if (!visited[p.Up().x][p.Up().y] && !vectorContains(p.Up(), stack) && p.y < -sideOver2) {
            visitables.push_back(p.Up());
            totalAvailable++;
          }
        
    if (RIGHT)
      if (!visited[p.Right().x][p.Right().y] && !vectorContains(p.Right(), stack) && p.x < sideOver2) {
            visitables.push_back(p.Right());
            totalAvailable++;
          }
          
    if (DOWN)
      if (!visited[p.Down().x][p.Down().y] && !vectorContains(p.Down(), stack) && p.y < sideOver2) {
            visitables.push_back(p.Down());
            totalAvailable++;
         }
         
    if (LEFT)
      if (!visited[p.Left().x][p.Left().y] && !vectorContains(p.Left(), stack) && p.x < -sideOver2) {
            visitables.push_back(p.Left());
            totalAvailable++;
            }
          

    //for (int i = 0; i < totalAvailable; i++)
    //{
    //  std::cout << visitables[i].x << " " << visitables[i].y << std::endl;
    //}

  return visitables;
}
