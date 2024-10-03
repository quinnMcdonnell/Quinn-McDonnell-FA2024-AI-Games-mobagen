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
      if (!stack.empty()) {
          w->SetNodeColor(stack[stack.size() - 1], Color::Black);
          stack.pop_back();
        return true;
      }
      else
      {
          for (int i = 0; i < stack.size() - 1; i++)
          {
          w->SetNodeColor(stack[i], Color::Black);
        }
      }
      
    }

    if (visitables.size() > 1)
    {
      int random = rand() % visitables.size();
      auto next = visitables[random];
      
      auto delta = next - stack[stack.size() - 1];

      if (delta.x == 1) {
        w->SetEast(stack[stack.size() - 1], false);
        w->SetWest(next, false);
      }

      if (delta.x == -1) {
        w->SetWest(stack[stack.size() - 1], false);
        w->SetEast(next, false);
      }

      if (delta.y == 1) {
        w->SetSouth(stack[stack.size() - 1], false);
        w->SetNorth(next, false);
      }

      if (delta.y == -1) {
        w->SetNorth(stack[stack.size() - 1], false);
        w->SetSouth(next, false);
      }
      
      stack.push_back(next);
      visited[next.x][next.y] = true;
      w->SetNodeColor(next, Color::Red);



    } else {
      auto next = visitables[0];

      auto delta = next - stack[stack.size() - 1];

      if (delta.x == 1)
      {
        w->SetEast(stack[stack.size() - 1], false);
        w->SetWest(next, false);
      }

      if (delta.x == -1) {
        w->SetWest(stack[stack.size() - 1], false);
        w->SetEast(next, false);
      }

      if (delta.y == 1) {
        w->SetSouth(stack[stack.size() - 1], false);
        w->SetNorth(next, false);
      }

      if (delta.y == -1) {
        w->SetNorth(stack[stack.size() - 1], false);
        w->SetSouth(next, false);
      }

      stack.push_back(next);
      visited[next.x][next.y] = true;
      w->SetNodeColor(next, Color::Red);

    }
     
  }

    return true;
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

int totalAvailable = 0;
 
    if (!visited[p.Up().x][p.Up().y] && !vectorContains(p.Up(), stack) && p.y > -sideOver2) {
            visitables.push_back(p.Up());
            totalAvailable++;
          }
        
      if (!visited[p.Right().x][p.Right().y] && !vectorContains(p.Right(), stack) && p.x < sideOver2) {
            visitables.push_back(p.Right());
            totalAvailable++;
          }
          
      if (!visited[p.Down().x][p.Down().y] && !vectorContains(p.Down(), stack) && p.y < sideOver2) {
            visitables.push_back(p.Down());
            totalAvailable++;
         }
         
      if (!visited[p.Left().x][p.Left().y] && !vectorContains(p.Left(), stack) && p.x > -sideOver2) {
            visitables.push_back(p.Left());
            totalAvailable++;
            }
          

    //for (int i = 0; i < totalAvailable; i++)
    //{
    //  std::cout << visitables[i].x << " " << visitables[i].y << std::endl;
    //}

  return visitables;
}
