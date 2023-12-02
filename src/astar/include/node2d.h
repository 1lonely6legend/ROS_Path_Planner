//
// Created by ogier on 23-11-29.
//

#ifndef ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_NODE2D_H_
#define ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_NODE2D_H_
#include<ros/ros.h>
#include<vector>
#include "constants.h"
class Node2d {
  //定义的二维节点结构
 public:
  Node2d() : x(0), y(0), solid(false), open(true), pre(nullptr), G(0), H(0), C(0) {}
  Node2d(int x, int y) : x(x), y(y), solid(false), open(true), pre(nullptr), G(0), H(0), C(0) {}
  void set_x(float x);
  void set_y(float y);
  void set_used();
  void set_soild();
  //是否可以通过,默认可通过
  bool solid;
  //是否被访问过,ture = open 未被访问，默认未被访问
  bool open;
  //节点的xy坐标
  double x;
  double y;
  //当前节点的前向节点
  Node2d *pre;
  //走位位置的代价
  float G;
  //启发式函数的预期代价
  float H;
  //总的代价
  float C;
  void update_G();
  void update_H(Node2d &goal);
  void update_C();
};
#endif //ROS_PATH_PLANNER_SRC_ASTAR_INCLUDE_NODE2D_H_
