#include "planner.h"

Planner::Planner() {
  ROS_INFO_STREAM("creat Planner instance, start subscribe");
}

void Planner::set_start(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &start_position) {
  start_node.set_x(start_position->pose.pose.position.x);
  start_node.set_y(start_position->pose.pose.position.y);
  start_node.set_used();
  validStart = true;
}

void Planner::set_goal(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &goal_position) {
  goal_node.set_x(goal_position->pose.pose.position.x);
  goal_node.set_y(goal_position->pose.pose.position.y);
  goal_node.set_used();
  validGoal = true;
}

void Planner::setMap(const nav_msgs::OccupancyGrid::ConstPtr &grid) {
  plan_map.update(grid);
}

void Planner::plan() {
  if(validGoal&&validStart)
  Astar As();
}