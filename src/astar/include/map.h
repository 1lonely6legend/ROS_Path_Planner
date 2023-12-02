//
// Created by ogier on 23-11-29.
//
#ifndef ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_MAP_H_
#define ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_MAP_H_
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <vector>
#include "constants.h"
#include "node2d.h"
using std::vector;
class Map {
  //定义的地图类
 public:
  Map(){};
  //更新地图信息
  void update(const nav_msgs::OccupancyGrid::ConstPtr &);
  vector<vector<Node2d>>mapData;
 private:
  int _originx;
  int _originy;
  float _resolution;
  int _width;
  int _height;

};

#endif //ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_MAP_H_
