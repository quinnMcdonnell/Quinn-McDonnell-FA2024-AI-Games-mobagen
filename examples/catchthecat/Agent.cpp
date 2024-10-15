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

  ASNode(Point2D p, int h)
  { 
    point = p;
    heuristicDist = h;
  }

  Point2D getPoint() { return point; }

  bool operator<(const ASNode& rhs) const 
  { 
      return heuristicDist + accDist > rhs.heuristicDist + rhs.accDist; 
  }
};

int heuristics(Point2D p, int sideSizeOver2)
{ 
    //right
    if (p.x > abs(p.y)) return sideSizeOver2 - p.x;

    // down
    if (-p.y > abs(p.x)) return sideSizeOver2 + p.y;

    // left
    if (-p.x > abs(p.y)) return sideSizeOver2 + p.x;

    // up
    if (p.y > abs(p.x)) return sideSizeOver2 - p.y;
}


std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<ASNode> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push({catPos, heuristics(catPos, w->getWorldSideSize()/2)});
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    auto current = frontier.top();
    
    // remove the current from frontierset
    frontierSet.erase(current.getPoint());
    
    // mark current as visited
    visited.insert({current.getPoint(), true});

    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> neighbors = getsVisitablesNeighbors(w, &current.getPoint());
    
    // iterate over the neighs:
    


    // for every neighbor set the cameFrom
    
    // enqueue the neighbors to frontier and frontierset
    
    // do this up to find a visitable border and break the loop

  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

//bool vectorContains(const Point2D& p, const std::vector<Point2D>& v) { return std::find(v.begin(), v.end(), p) != v.end(); }

std::vector<Point2D> getsVisitablesNeighbors(World* w, const Point2D& current)
{
  auto sideOver2 = w->getWorldSideSize() / 2;
  std::vector<Point2D> visitables;

  visitables.push_back(current.Right());
  visitables.push_back({current.x + 1, current.y + 1});
  visitables.push_back(current.Down());
  visitables.push_back(current.Left());
  visitables.push_back({current.x - 1, current.y - 1});
  visitables.push_back(current.Up());

  return visitables;
}
