#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <iostream>

 
Point2D Cat::Move(World* world) {
   auto rand = Random::Range(0, 5);
   auto pos = world->getCat();
   auto path = generatePath(world);

   if (path.size() > 0)
   {
     //std::cout << "Path hit" << std::endl;

     for (int i = 0; i < path.size(); i++)
     {
       std::cout << path[i].x << " " << path[i].y << std::endl;
     }
     std::cout << "move: " << path.back().x << " " << path.back().y << std::endl;
     std::cout << "Cat Loc: " << pos.x << " " << pos.y << std::endl;
     std::cout << std::endl;
     return path.back();
   }

   //Include the Pathfinding here
   std::cout << "Rand hit" << std::endl;
   switch (rand) {
     case 0:
       return World::NE(pos);
     case 1:
       return World::NW(pos);
     case 2:
       return World::E(pos);
     case 3:
       return World::W(pos);
     case 4:
       return World::SW(pos);
     case 5:
       return World::SE(pos);
     default:
       throw "random out of range";
   }
 }

