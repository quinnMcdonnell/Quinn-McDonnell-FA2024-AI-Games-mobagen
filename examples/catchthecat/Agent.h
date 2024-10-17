#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  struct ASNode {
    Point2D point;
    int accDist;
    int heuristicDist;

    ASNode(Point2D p, int h) {
      point = p;
      heuristicDist = h;
    }

    Point2D getPoint() { return point; }

    bool operator<(const ASNode& rhs) const { return heuristicDist + accDist > rhs.heuristicDist + rhs.accDist; }
  };
	
	explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
};

#endif  // AGENT_H
