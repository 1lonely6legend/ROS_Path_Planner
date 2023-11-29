//
// Created by ogier on 23-11-29.
//
#include "node2d.h"
void Node2d::set_x(float x) {
  _x = x;
}
void Node2d::set_y(float y) {
  _y = y;
}
void Node2d::set_used() {
  open = false;
};
void Node2d::set_soild() {
  solid = true;
};
void Node2d::set_G(int num) {
  G = num;
}
void Node2d::set_H(int num) {
  H = num;
}
void Node2d::set_C(int num) {
  C = num;
}
