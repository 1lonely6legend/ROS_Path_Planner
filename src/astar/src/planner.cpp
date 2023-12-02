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

void Planner::set_goal(const geometry_msgs::PoseStamped::ConstPtr &goal_position) {
  goal_node.set_x(goal_position->pose.position.x);
  goal_node.set_y(goal_position->pose.position.y);
  goal_node.set_used();
  validGoal = true;
}

void Planner::setMap(const nav_msgs::OccupancyGrid::ConstPtr &grid) {
  plan_map.update(grid);
}

void Planner::plan() {
  std::list<Node2d *> res;
  if (validGoal && validStart) {
    Astar As;
    res = As.calculate_path(start_node, goal_node, plan_map);
  }
  nav_msgs::Path pub_path;
  pub_path.header.frame_id = "map";
  pub_path.header.stamp = ros::Time::now();
  pub_path.poses.clear();
  for (auto p : res) {
    geometry_msgs::PoseStamped this_pose_stamped;
    this_pose_stamped.header.frame_id = "map";
    this_pose_stamped.header.stamp = ros::Time::now();
    this_pose_stamped.pose.position.x = p->x;
    this_pose_stamped.pose.position.y = p->y;

    this_pose_stamped.pose.orientation.x = 0;
    this_pose_stamped.pose.orientation.y = 0;
    this_pose_stamped.pose.orientation.z = 0;
    this_pose_stamped.pose.orientation.w = 0; //直接让四元数全为0了，省得
    pub_path.poses.push_back(this_pose_stamped);
    Path_pub.publish(pub_path);
  }
}