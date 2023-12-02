//
// Created by ogier on 23-11-29.
//
#include "node2d.h"
void Node2d::set_x(float x) {
  this->x = x;
}
void Node2d::set_y(float y) {
  this->y = y;
}
void Node2d::set_used() {
  open = false;
};
void Node2d::set_soild() {
  solid = true;
};

void Node2d::update_H(Node2d &goal) {
  //TODO:后续考虑加入不同的启发式函数，目前使用曼哈顿函数
  this->H = std::abs(this->x - goal.x) + std::abs(this->y - goal.y);
}

void Node2d::update_G() {
  //TODO:后续在进行斜向更新时，设置不同的代价
  this->G = this->pre->G + cost_zhi;
}

void Node2d::update_C() {
  this->C = this->H + this->G;
}