#include <board.h>
#include <piece.h>
#include <catch2/catch.hpp>

using checkers::Board;
using checkers::Piece;

TEST_CASE("Testing moving 1 square diagonally") {
  SECTION("Test Blue Piece moving left") {
    Board board;
    Piece piece = board.GetPiece(5,4);
    board.Move(piece, 4, 5);
    REQUIRE(board.GetPiece(4,5).GetColor() == ci::Color("blue"));
  }
  SECTION("Test Blue Piece moving right") {
    Board board;
    Piece piece = board.GetPiece(5,4);
    board.Move(piece, 4, 3);
    REQUIRE(board.GetPiece(4,3).GetColor() == ci::Color("blue"));
  }
  SECTION("Test Black Piece moving left") {
    Board board;
    Piece piece = board.GetPiece(2,3);
    board.Move(piece, 3, 2);
    REQUIRE(board.GetPiece(3,2).GetColor() == ci::Color("black"));
  }
  SECTION("Test Black Piece moving right") {
    Board board;
    Piece piece = board.GetPiece(2,3);
    board.Move(piece, 3, 4);
    REQUIRE(board.GetPiece(3,4).GetColor() == ci::Color("black"));
  }
}

TEST_CASE("Testing that pieces become King on last rows") {
  SECTION("Test Blue Square becoming king") {
    Board board;
    board.GetPiece(0,1).SetAlive(false);
    Piece piece = board.GetPiece(5,4);
    board.Move(piece, 0,1);
    REQUIRE(board.GetPiece(0,1).IsKing() == true);
  }

  SECTION("Test Black Square becoming king") {
    Board board;
    board.GetPiece(7,0).SetAlive(false);
    Piece piece = board.GetPiece(0,1);
    board.Move(piece, 7,0);
    REQUIRE(board.GetPiece(7,0).IsKing() == true);
  }
}