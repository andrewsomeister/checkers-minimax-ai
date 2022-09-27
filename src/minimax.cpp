#pragma once
using namespace std;
#include "minimax.h"
#include <board.h>
namespace checkers {
tuple<Board, double> Minimax::ReturnBestMove(Board board, int depth,
                                            bool ai_turn) {
  if (depth == 0 || board.CheckWinner()) {
    return make_tuple(board, board.Evaluate());
  }
  if (ai_turn) {
    float best_evaluation = 100;
    Board best_move;
    for (Board move : GetAllBoards(board, ci::Color("black"))) {
      double eval = get<1>(ReturnBestMove(move, depth - 1, false));
      best_evaluation = min(best_evaluation, (float)(eval));
      if (best_evaluation == eval) {
        best_move = move;
      }
    }
    return make_tuple(best_move, best_evaluation);
  } else {
    float best_evaluation = -100;
    Board best_move;
    for (Board move : GetAllBoards(board, ci::Color("blue"))) {
      double eval = get<1>(ReturnBestMove(move, depth - 1, true));
      best_evaluation = max(best_evaluation, (float)(eval));
      if (best_evaluation == eval) {
        best_move = move;
      }
    }
    return make_tuple(best_move, best_evaluation);
  }
}

Board Minimax::SimulateMove(Board board, Piece piece, int moveRow, int moveCol,
                            vector<Piece> skipped) {
  board.Move(piece, moveRow, moveCol);
  if (!skipped.empty()) {
    board.Remove(skipped);
  }
  return board;
}

vector<Board> Minimax::GetAllBoards(Board board, cinder::ColorT<float> color) {
  vector<Board> moves;
  map<tuple<int, int>, vector<Piece>> valid_moves;
  for (Piece piece : board.GetPieces(color)) {
    valid_moves = board.GetValidMoves(piece);
    for (auto const& move : valid_moves) {
      Board temp_board = board;
      Piece temp_piece = temp_board.GetPiece(piece.GetRow(), piece.GetCol());
      Board new_board = SimulateMove(temp_board, temp_piece, get<0>(move.first),
                                     get<1>(move.first), move.second);
      moves.push_back(new_board);
    }
  }
  return moves;
}
}