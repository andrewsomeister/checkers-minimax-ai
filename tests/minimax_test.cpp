#include <board.h>
#include <minimax.h>
#include <catch2/catch.hpp>

using checkers::Board;
using checkers::Piece;
using checkers::Minimax;

TEST_CASE("Test minimax plays the best move") {
  SECTION("Test eating piece when advantageous") {
    Board board = {};
    board.SetPieceColor(3,4,ci::Color("blue"));
    board.SetPieceAlive(5,4);
    board.SetPieceAlive(5,6);
    Board new_board = std::get<0>(Minimax::ReturnBestMove(board, 4, true));
    REQUIRE(new_board.GetPiece(4,5).GetColor() == ci::Color("black"));
  }

  SECTION("Test double jumping when advantageous") {
    Board board = {};
    board.SetPieceColor(3,4,ci::Color("blue"));
    board.SetPieceAlive(6,3);
    Board new_board = std::get<0>(Minimax::ReturnBestMove(board, 4, true));
    REQUIRE(new_board.GetPiece(6,3).GetColor() == ci::Color("black"));
  }

  SECTION("Test becoming king when advantageous") {
    Board board = {};
    board.SetPieceColor(6,7,ci::Color("black"));
    board.SetPieceAlive(7,6);
    Board new_board = std::get<0>(Minimax::ReturnBestMove(board, 4, true));
    REQUIRE(new_board.GetPiece(7,6).GetColor() == ci::Color("black"));
  }
}