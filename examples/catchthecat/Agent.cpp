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

  Point2D getPoint() { return point; }

  bool operator<(const ASNode& rhs) const 
  { 
      return heuristicDist + accDist > rhs.heuristicDist + rhs.accDist; 
  }
};

int heuristics(Point2D p, int sideSizeOver2)
{ 
    if (p.x - p.y > 0 && p.x + p.y > 0) return sideSizeOver2 - p.x;
}

//// bootstrap
 /*Point2D start = {0, 0};
 Point2D end = {5, 5};*/

// queue.push(point = start, accDist = 0, heurdist = start.distanceTo(end));
////
// while (true) {
//   // todo: create break conditions
//   auto current : ASNode = queue.top();
//   //
//   // list of all visitables
//   // add neighbors to the queue, pay attention to add 1 unit of distance to the accDist from the current node set the heurDist from the neighbor to
//   // the end node queue.pop();
// }

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    auto current = frontier.front();
    
    // remove the current from frontierset
    frontier.pop();
    
    // mark current as visited
    visited.insert({current, true});
    
    // getVisitableNeighbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    
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

std::vector<Point2D> getsVisitablesNeighbors(World* w, const Point2D* current)
{
  auto sideOver2 = w->getWorldSideSize() / 2;
  std::vector<Point2D> visitables;

  //Check what's nearby

 /* if (camefrom[current->Up().x && p.y > -sideOver2) {
    visitables.push_back(p.Up());
  }*/

  //if (!visited[p.Right().x][p.Right().y] && !vectorContains(p.Right(), stack) && p.x < sideOver2) {
  //  visitables.push_back(p.Right());
  //}

  //if (!visited[p.Down().x][p.Down().y] && !vectorContains(p.Down(), stack) && p.y < sideOver2) {
  //  visitables.push_back(p.Down());
  //}

  //if (!visited[p.Left().x][p.Left().y] && !vectorContains(p.Left(), stack) && p.x > -sideOver2) {
  //  visitables.push_back(p.Left());
  //}

  return visitables;
}
