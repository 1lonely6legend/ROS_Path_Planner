#ifndef PLANNER_H
#define PLANNER_H
#include <iostream>
#include <ros/ros.h>
#include <vector>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include "node2d.h"
#include "astar.h"
#include "constants.h"
#include "map.h"

class Planner {
  //规划的入口，收集地图，起终点，使用plan函数进行具体算法规划
 public:
  Planner();
  void set_start(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &);
  void set_goal(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &);
  void setMap(const nav_msgs::OccupancyGrid::ConstPtr &);
  void plan();

 private:
  //申请句柄，监听地图信息，起始终止位置信息，并存放到对应的数据结构中
  ros::NodeHandle n;
  ros::Subscriber SubStart = n.subscribe("/initialpose", 1, &Planner::set_start, this);
  ros::Subscriber SubGoal = n.subscribe("/move_base_simple/goal", 1, &Planner::set_goal, this);
  ros::Subscriber SubMap = n.subscribe("/map", 1, &Planner::setMap, this);
  // 存放规划所需要的数据结构，起终点，地图
  Node2d start_node;
  // 标志位，如果设定好就转为TRUE
  bool validStart = false;
  Node2d goal_node;
  bool validGoal = false;
  Map plan_map;
  std::list<Node2d*> path;
};
#endif  // PLANNER_H