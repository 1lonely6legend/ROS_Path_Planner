//
// Created by ogier on 23-11-29.
//
#ifndef ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_ASTAR_H_
#define ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_ASTAR_H_

#include <list>
#include <queue>
#include <vector>
#include <unordered_map>
#include "constants.h"
#include "node2d.h"
#include "map.h"

class Astar {
 public:
  Astar() {};
  std::list<Node2d *> calculate_path(Node2d &start, Node2d &goal, Map &map);
  std::vector<Node2d*> get_surround_point(Node2d &node);
 private:
  Node2d _start_node;
  Node2d _goal_node;
  Map _plan_map;
};

#endif //ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_ASTAR_H_
