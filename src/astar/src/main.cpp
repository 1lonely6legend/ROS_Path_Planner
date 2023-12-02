#include <planner.h>
#include <iostream>
#include <ros/ros.h>
int main(int argc, char* argv[]) {
  ROS_INFO_STREAM("start main funtion" << std::endl);
  ros::init(argc,argv,"astar");
  Planner P;
  P.plan();
  ros::spin();
  return 0;
}