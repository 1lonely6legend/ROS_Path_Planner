//
// Created by ogier on 23-11-29.
//
#ifndef ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_ASTAR_H_
#define ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_ASTAR_H_

#include <list>
#include <queue>
#include <vector>
#include "constants.h"
#include "node2d.h"
#include "map.h"
class Astar {
 public:
  Astar(Map &map) : map(map){};
  void calculate() {

  }
 private:
  Map map;
  std::list<Node2d*> path;
};

#endif //ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_ASTAR_H_
