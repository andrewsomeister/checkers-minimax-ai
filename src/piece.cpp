#pragma once
#include "piece.h"
namespace checkers {
Piece::Piece() {
}

Piece::Piece(int row, int col, cinder::ColorT<float> color, bool is_alive) {
  row_ = row;
  col_ = col;
  color_ = color;
  is_king_ = false;
  position_[0] = 0;
  position_[1] = 0;
  is_alive_ = is_alive;
  CalculatePosition();
}

void Piece::CalculatePosition() {
    int offset = 100;
  position_[0] = offset + (float)kSquareSize * col_ + kSquareSize / 2;
  position_[1] = offset + (float)kSquareSize * row_ + kSquareSize / 2;
}

void Piece::MakeKing() {
  is_king_ = true;
}

void Piece::Display() {
  float radius = (float)kSquareSize / 2 - kPadding;
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(position_, radius);
  ci::gl::drawSolidCircle(position_, radius);
  if (is_king_) {
    ci::gl::color(ci::Color("green"));
    ci::gl::drawSolidCircle(position_, kCircleSize);
  }
}

void Piece::Move(int row, int col) {
  row_ = row;
  col_ = col;
  CalculatePosition();
}

cinder::ColorT<float> Piece::GetColor() {
  return color_;
}

bool Piece::IsAlive() {
  return is_alive_;
}

int Piece::GetRow() {
  return row_;
}

int Piece::GetCol() {
  return col_;
}

void Piece::SetAlive(bool alive) {
  is_alive_ = alive;
}

bool Piece::IsKing() {
  return is_king_;
}

void Piece::SetColor(cinder::ColorT<float> color) {
  color_ = color;
}
}
