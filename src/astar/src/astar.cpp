//
// Created by ogier on 23-11-29.
//
#include <list>
#include "astar.h"

struct CompareNode2d {
  bool operator()(const Node2d *N1, const Node2d *N2) const {
    return N1->C > N2->C;
  }
};

std::list<Node2d *> Astar::calculate_path(Node2d &start, Node2d &goal, Map &map) {
  //实际的搜索函数

  _start_node = start;
  _goal_node = goal;
  _plan_map = map;

  //一个按照节点总cost值排序的小顶堆
  std::priority_queue<Node2d *, vector<Node2d *>, CompareNode2d> que;
  que.push(&start);
  start.G = 0;
  start.update_H(goal);
  start.update_C();
  start.open = false;

  std::unordered_map<Node2d *, Node2d *> came_from;

  while (!que.empty()) {
    Node2d *cur = que.top();
    que.pop();

    if (cur == &goal) {
      std::list<Node2d *> path;
      while (cur != &start) {
        path.push_back(cur);
        cur = came_from[cur];
      }
      path.push_front(&start);
      return path;
    }
    vector<Node2d *> sur = get_surround_point(*cur);
    for (Node2d *next : sur) {
      int newG = cur->G + cost_zhi;
      if (next->open == true || newG < next->G) {
        next->G = newG;
        next->update_H(goal);
        next->update_C();
        next->open = false;
        que.push(next);
        came_from[next] = cur;
      }
    }
  }
  return {};
}

std::vector<Node2d *> Astar::get_surround_point(Node2d &node) {
  //获取当前搜索节点的相邻节点
  //TODO:后续查找中添加周围八个节点，现在只有四个
  std::vector<Node2d *> res;
  for (int x = node.x - 1; x <= node.x + 1; ++x) {
    for (int y = node.y - 1; y <= node.y + 1; ++y) {
      if (x == node.x && y == node.y)
        continue;
      if (_plan_map.mapData[x][y].open == true)
        res.push_back(&_plan_map.mapData[x][y]);
    }
  }
  return res;
}
