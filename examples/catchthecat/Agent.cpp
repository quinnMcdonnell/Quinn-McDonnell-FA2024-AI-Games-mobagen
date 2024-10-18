#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

struct ASNode {
  Point2D point;
  int accDist;
  int heuristicDist;

  ASNode(Point2D p, int h, int acc): point(p), heuristicDist(h), accDist(acc){}

  Point2D getPoint() { return point; }

  bool operator<(const ASNode& rhs) const 
  { 
      return heuristicDist + accDist > rhs.heuristicDist + rhs.accDist; 
  }
};

int heuristics(Point2D p, int sideSizeOver2)
{ 
    //right
  if (p.x - p.y > 0 && p.x + p.y > 0)
    return (sideSizeOver2 / 2) - p.x;

    if (p.x - p.y > 0 && p.x + p.y < 0) 
        return (sideSizeOver2 / 2) - p.x;

    if (p.x - p.y < 0 && p.x + p.y < 0) 
        return (sideSizeOver2 / 2) - p.x;

    if (p.x - p.y < 0 && p.x + p.y > 0) 
        return (sideSizeOver2 / 2) - p.x;

    return sideSizeOver2;
}

std::vector<Point2D> getsVisitablesNeighbors(World* w, const Point2D& current, unordered_map<Point2D, bool> m) {
  auto sideOver2 = w->getWorldSideSize() / 2;
  std::vector<Point2D> visitables;

 /* auto c = current.Right();
  auto ca = w->getCat();
  auto fi = m.find(current) != m.end();*/

  if (!m.contains(current.Right()) 
      && current.Right() != w->getCat() 
      && !w->getContent(current.Right())) 
      visitables.push_back(current.Right());

  Point2D lt = {current.Left().x, current.y + 1};
  if (!m.contains({current.Left().x, current.y + 1}) 
      && lt != w->getCat() 
      && !w->getContent({current.Left().x, current.y + 1})) 
      visitables.push_back({current.Left().x, current.y + 1});

  if (!m.contains(current.Down()) 
      && current.Down() != w->getCat() 
      && !w->getContent(current.Down())) 
      visitables.push_back(current.Down());

  if (!m.contains(current.Left()) 
      && current.Left() != w->getCat() 
      && !w->getContent(current.Left())) 
      visitables.push_back(current.Left());

  Point2D lb = {current.Left().x, current.y - 1};
  if (!m.contains({current.Left().x, current.y - 1}) 
      && lb != w->getCat()
      && !w->getContent({current.Left().x, current.y - 1})) 
      visitables.push_back({current.Left().x, current.y - 1});

  if (!m.contains(current.Up()) 
      && current.Up() != w->getCat() 
      && !w->getContent(current.Up())) 
      visitables.push_back(current.Up());

  return visitables;
}

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<ASNode> frontier;           // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.emplace(catPos, heuristics(catPos, w->getWorldSideSize()/2), 0);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    auto current = frontier.top();
    frontier.pop();
    
    // remove the current from frontierset
    frontierSet.erase(current.getPoint());
    
    // mark current as visited
    visited.insert({current.getPoint(), true});

    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> neighbors = getsVisitablesNeighbors(w, current.getPoint(), visited);
    
    // iterate over the neighs:
    for (int i = 0; i < neighbors.size(); i++)
    {
      if (visited.contains(neighbors[i]) || frontierSet.contains(neighbors[i])) 
          continue;

      cameFrom[neighbors[i]] = current.getPoint();

      if (w->catWinsOnSpace(neighbors[i])) {
        borderExit = neighbors[i];

        break;
      }

      frontier.emplace(neighbors[i], heuristics(neighbors[i], w->getWorldSideSize() / 2), current.accDist + 1);
      frontierSet.insert(neighbors[i]);
    }

    if (borderExit != Point2D::INFINITE)
    {
      break;
    }
  }

  
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  if (borderExit != Point2D::INFINITE) {
    std::vector<Point2D> path;
    auto current = borderExit;
      while(current != w->getCat())
      {
       path.push_back(current);
       current = cameFrom[current];
      }

      return path;
  }
  else
  {
    // if there isnt a reachable border, just return empty vector
    return vector<Point2D>();
  }
  
}
