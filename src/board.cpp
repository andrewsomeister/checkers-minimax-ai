#pragma once
#include "../include/board.h"
#include <piece.h>
using glm::vec2;
namespace checkers {

Board::Board() {
  blue_left_ = 12.0;
  black_left_ = 12.0;
  blue_kings_ = 0.0;
  black_kings_ = 0.0;
  CreateBoard();
}

double Board::Evaluate() {
  return blue_left_ - black_left_ + (blue_kings_ * 0.25) -
      (black_kings_ * 0.25);
}

vector<Piece> Board::GetPieces(cinder::ColorT<float> color) {
  vector<Piece> pieces;
  for (vector<Piece> row : board_) {
    for (Piece piece : row) {
      if (piece.GetColor() == color && piece.IsAlive()) {
        pieces.push_back(piece);
      }
    }
  }
  return pieces;
}

void Board::Move(Piece &piece, int row, int col) {
  board_[piece.GetRow()][piece.GetCol()].SetAlive(false);
  piece.Move(row, col);
  board_[row][col].Move(piece.GetRow(), piece.GetCol());
  board_[piece.GetRow()][piece.GetCol()] = board_[row][col];
  board_[row][col] = piece;
  if ((row == kRows - 1 || row == 0) && !board_[row][col].IsKing()) {
    board_[row][col].MakeKing();
    if (piece.GetColor() == ci::Color("blue")) {
      blue_kings_ = blue_kings_ + 1;
    } else {
      black_kings_ = black_kings_ + 1;
    }
  }
}

void Board::Display() {
  DrawSquares();
  for (int row = 0; row < kRows; row++) {
    for (int col = 0; col < kCols; col++) {
      if (board_[row][col].IsAlive()) {
        board_[row][col].Display();
      }
    }
  }
}

void Board::CreateBoard() {
  for (int row = 0; row < kRows; row++) {
    board_.push_back(std::vector<Piece>());
    for (int col = 0; col < kCols; col++) {
      if (col % 2 == ((row + 1) % 2)) {
        if (row < 3) {
          board_[row].push_back(Piece(row, col, "black", true));
        } else if (row > 4) {
          board_[row].push_back(Piece(row, col, "blue", true));
        } else {
          board_[row].push_back(Piece(row, col, "yellow", false));
        }
      } else {
        board_[row].push_back(Piece(row, col, "yellow", false));
      }
    }
  }
}

void Board::DrawSquares() {
  for (int row = 0; row < kRows; row++) {
    for (int col = 0; col < kCols; col++) {
      if (col % 2 == ((row + 1) % 2)) {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidRect(
            ci::Rectf(vec2(kSquareSize * row, kSquareSize * col),
                      vec2(kSquareSize * (row + 1), kSquareSize * (col + 1))));
      } else {
        ci::gl::color(ci::Color("red"));
        ci::gl::drawSolidRect(
            ci::Rectf(vec2(kSquareSize * row, kSquareSize * col),
                      vec2(kSquareSize * (row + 1), kSquareSize * (col + 1))));
      }
    }
  }
}

Piece Board::GetPiece(int row, int col) {
  return board_[row][col];
}

map<tuple<int, int>, vector<Piece>> Board::GetValidMoves(Piece piece) {
  map<tuple<int, int>, vector<Piece>> moves;
  int left = piece.GetCol() - 1;
  int right = piece.GetCol() + 1;
  int row = piece.GetRow();

  if (piece.GetColor() == ci::Color("black") || piece.IsKing()) {
    map<tuple<int, int>, vector<Piece>> left_moves = CheckMovesLeft(
        row + 1, std::min(kRows, row + 3), 1, piece.GetColor(), left);
    moves.insert(left_moves.begin(), left_moves.end());

    map<tuple<int, int>, vector<Piece>> right_moves = CheckMovesRight(
        row + 1, std::min(kRows, row + 3), 1, piece.GetColor(), right);
    moves.insert(right_moves.begin(), right_moves.end());
  }

  if (piece.GetColor() == ci::Color("blue") || piece.IsKing()) {
    map<tuple<int, int>, vector<Piece>> left_moves =
        CheckMovesLeft(row - 1, max(-1, row - 3), -1, piece.GetColor(), left);
    moves.insert(left_moves.begin(), left_moves.end());

    map<tuple<int, int>, vector<Piece>> right_moves = CheckMovesRight(
        row - 1, std::max(-1, row - 3), -1, piece.GetColor(), right);
    moves.insert(right_moves.begin(), right_moves.end());
  }
  return moves;
}

map<tuple<int, int>, vector<Piece>> Board::CheckMovesLeft(
    int start, int end, int step, cinder::ColorT<float> color, int col,
    std::vector<Piece> skipped) {
  map<tuple<int, int>, vector<Piece>> moves;
  vector<Piece> last;
  for (int row = start; row != end; row += step) {
    if (col < 0) {
      break;
    }
    if (row < 0) {
      break;
    }
    Piece current_piece = board_[row][col];
    if (!current_piece.IsAlive()) {
      if (!skipped.empty() && last.empty()) {
        break;
      } else if (!skipped.empty()) {
        vector<Piece> all_skipped = last;
        all_skipped.insert(all_skipped.end(), skipped.begin(), skipped.end());
        moves.insert(make_pair(make_tuple(row, col), all_skipped));
      } else {
        moves.insert(make_pair(make_tuple(row, col), last));
      }

      if (!last.empty()) {
        int newRow;
        if (step == -1) {
          newRow = max(row - 3, 0);
        } else {
          newRow = min(row + 3, kRows);
        }
        map<tuple<int, int>, vector<Piece>> left_moves =
            CheckMovesLeft(row + step, newRow, step, color, col - 1, last);
        moves.insert(left_moves.begin(), left_moves.end());
        map<tuple<int, int>, vector<Piece>> right_moves =
            CheckMovesRight(row + step, newRow, step, color, col + 1, last);
        moves.insert(right_moves.begin(), right_moves.end());
      }
      break;
    } else if (current_piece.GetColor() == color) {
      break;
    } else {
      last = {};
      last.push_back(current_piece);
    }
    col -= 1;
  }
  return moves;
}

map<tuple<int, int>, vector<Piece>> Board::CheckMovesRight(
    int start, int end, int step, cinder::ColorT<float> color, int col,
    std::vector<Piece> skipped) {
  map<tuple<int, int>, vector<Piece>> moves;
  vector<Piece> last;
  for (int row = start; row != end; row += step) {
    if (col >= kCols) {
      break;
    }
    if (row < 0) {
      break;
    }
    Piece current_piece = board_[row][col];
    if (!current_piece.IsAlive()) {
      if (!skipped.empty() && last.empty()) {
        break;
      } else if (!skipped.empty()) {
        vector<Piece> all_skipped = last;
        all_skipped.insert(all_skipped.end(), skipped.begin(), skipped.end());
        moves.insert(make_pair(make_tuple(row, col), all_skipped));
      } else {
        moves.insert(make_pair(make_tuple(row, col), last));
      }

      if (!last.empty()) {
        int newRow;
        if (step == -1) {
          newRow = max(row - 3, 0);
        } else {
          newRow = min(row + 3, kRows);
        }
        map<tuple<int, int>, vector<Piece>> left_moves =
            CheckMovesLeft(row + step, newRow, step, color, col - 1, last);
        moves.insert(left_moves.begin(), left_moves.end());
        map<tuple<int, int>, vector<Piece>> right_moves =
            CheckMovesRight(row + step, newRow, step, color, col + 1, last);
        moves.insert(right_moves.begin(), right_moves.end());
      }
      break;
    } else if (current_piece.GetColor() == color) {
      break;
    } else {
      last = {};
      last.push_back(current_piece);
    }
    col += 1;
  }
  return moves;
}

void Board::Remove(std::vector<Piece> pieces) {
  for (Piece piece : pieces) {
    board_[piece.GetRow()][piece.GetCol()].SetAlive(false);
    if (piece.IsAlive()) {
      if (piece.GetColor() == ci::Color("black")) {
        black_left_--;
      } else {
        blue_left_--;
      }
    }
  }
}

bool Board::CheckWinner() {
  return black_left_ <= 0 || blue_left_ <= 0;
}

void Board::SetPieceColor(int row, int col, cinder::ColorT<float> color) {
  board_[row][col].SetColor(color);
  if (!board_[row][col].IsAlive()) {
    board_[row][col].SetAlive(true);
  }
}

void Board::SetPieceAlive(int row, int col) {
  board_[row][col].SetAlive(false);
}

void Board::SetPieceKing(int row, int col) {
  board_[row][col].MakeKing();
  if (board_[row][col].GetColor() == ci::Color("blue")) {
    blue_kings_++;
  } else {
    black_kings_++;
  }
}

}