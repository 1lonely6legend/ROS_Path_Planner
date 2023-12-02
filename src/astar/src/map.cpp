//
// Created by ogier on 23-11-29.
//
#include"map.h"
void Map::update(const nav_msgs::OccupancyGrid::ConstPtr &grid) {
  ROS_INFO_STREAM("receiving map");
  _resolution = grid->info.resolution;
  _originx = grid->info.origin.position.x;
  _originy = grid->info.origin.position.y;
  _width = grid->info.width;
  _height = grid->info.height;
  //首先为二维数组分配内存，减少扩容开销
  mapData.resize(_height);
  for (auto &vec : mapData)
    vec.resize(_width);
  //读取/map话题中的一维数组，放置在二维数组的对应位置
  // yyyyyyyyyyyyyyyyyyyyyyy
  //x
  //x
  //x
  //x
  for (int x = 0; x < _height; ++x)
    for (int y = 0; y < _width; ++y){
      Node2d temp(x,y);
      if(grid->data[x*_width+y]==100){
        //100代表该节点不能通过
        temp.set_soild();
      }
      mapData[x].push_back(temp);
    }
}