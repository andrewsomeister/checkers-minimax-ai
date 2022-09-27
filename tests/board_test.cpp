#include <board.h>
#include <piece.h>
#include <catch2/catch.hpp>
#include <algorithm>
#include <vector>

using checkers::Board;
using checkers::Piece;

using namespace std;

TEST_CASE("Test Evaluate") {
  SECTION("Test Evaluate on a full board") {
    Board board;
    REQUIRE(board.Evaluate() == 0);
  }

  SECTION("Test Evaluate on a partial board") {
    Board board;
    vector<Piece> toRemove;
    toRemove.push_back(board.GetPiece(5,4));
    board.Remove(toRemove);
    REQUIRE(board.Evaluate() == -1);
  }

  SECTION("Test Evaluate on board with 1 king") {
    Board board;
    board.SetPieceKing(5,4);
    REQUIRE(board.Evaluate() == 1);
  }

  SECTION("Test Evaluate on board with 1 and 2 kings on each side") {
    Board board;
    board.SetPieceKing(5,4);
    board.SetPieceKing(2,5);
    board.SetPieceKing(2,7);
    REQUIRE(board.Evaluate() == -1);
  }
}

TEST_CASE("Test CreateBoard") {
  SECTION("Test correct location of each piece") {
    Board board;
    REQUIRE(board.GetPiece(0,0).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(0,1).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(0,2).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(0,3).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(0,4).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(0,5).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(0,6).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(0,7).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(1,0).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(1,1).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(1,2).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(1,3).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(1,4).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(1,5).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(1,6).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(1,7).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(2,0).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(2,1).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(2,2).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(2,3).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(2,4).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(2,5).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(2,6).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(2,7).GetColor() == ci::Color("black"));
    REQUIRE(board.GetPiece(3,0).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,1).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,2).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,3).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,4).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,5).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,6).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(3,7).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,0).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,1).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,2).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,3).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,4).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,5).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,6).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(4,7).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(5,0).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(5,1).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(5,2).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(5,3).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(5,4).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(5,5).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(5,6).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(5,7).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(6,0).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(6,1).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(6,2).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(6,3).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(6,4).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(6,5).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(6,6).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(6,7).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(7,0).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(7,1).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(7,2).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(7,3).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(7,4).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(7,5).GetColor() == ci::Color("yellow"));
    REQUIRE(board.GetPiece(7,6).GetColor() == ci::Color("blue"));
    REQUIRE(board.GetPiece(7,7).GetColor() == ci::Color("yellow"));
  }
}

TEST_CASE("Test Getting Valid Moves for single moves") {
  SECTION("Get Valid Moves for blue piece in middle of board with 2 possible moves") {
    Board board;
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,4));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,3)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,5)) != locations.end());
  }

  SECTION("Get Valid Moves for black piece in middle of board with 2 possible moves") {
    Board board;
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,3));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(find(locations.begin(), locations.end(), make_tuple(3,2)) != locations.end());
    REQUIRE(find(locations.begin(), locations.end(), make_tuple(3,4)) != locations.end());
  }

  SECTION("Get Valid Moves for blue piece blocked by another blue piece with only 1 possible move") {
    Board board;
    board.SetPieceColor(4,3,ci::Color("blue"));
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,4));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(find(locations.begin(), locations.end(), make_tuple(4,3)) == locations.end());
    REQUIRE(find(locations.begin(), locations.end(), make_tuple(4,5)) != locations.end());
  }

  SECTION("Get Valid Moves for black piece blocked by another blue piece with only 1 possible move") {
    Board board;
    board.SetPieceColor(3,2,ci::Color("black"));
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,3));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,2)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,4)) != locations.end());
  }

  SECTION("Get Valid Moves for blue piece blocked by 2 other blue pieces with no possible moves") {
    Board board;
    board.SetPieceColor(4,3,ci::Color("blue"));
    board.SetPieceColor(4,5,ci::Color("blue"));
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,4));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,3)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,5)) == locations.end());
  }

  SECTION("Get Valid Moves for black piece blocked by 2 other blue pieces with no possible moves") {
    Board board;
    board.SetPieceColor(3,2,ci::Color("black"));
    board.SetPieceColor(3,4,ci::Color("black"));
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,3));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,2)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,4)) == locations.end());
  }

  SECTION("Get Valid Moves for blue on left edge of map with one possible move") {
    Board board;
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,0));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,1)) != locations.end());
  }

  SECTION("Get Valid Moves for black piece blocked by 2 other blue pieces with no possible moves") {
    Board board;
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,7));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,6)) != locations.end());
  }

  SECTION("Get Valid Moves for blue on left edge of map with one possible move") {
    Board board;
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,0));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,1)) != locations.end());
  }

  SECTION("Get Valid Moves for black on left edge of map with one possible move") {
    Board board;
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,7));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,6)) != locations.end());
  }
}

TEST_CASE("Test Getting Valid Moves for jump moves") {
  SECTION("Get Valid Moves for blue piece with one possible jump and one regular move") {
    Board board;
    board.SetPieceColor(4,5,ci::Color("black"));
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,4));
    vector<tuple<int,int>> locations;
    vector<Piece> removed;
    for(auto const& x : moves) {
      locations.push_back(x.first);
      removed.insert(removed.begin(), x.second.begin(), x.second.end());
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,3)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,5)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,6)) != locations.end());
    REQUIRE(removed[0].GetRow() == 4);
    REQUIRE(removed[0].GetCol() == 5);
  }

  SECTION("Get Valid Moves for black piece with one possible jump and one regular move") {
    Board board;
    board.SetPieceColor(3,4,ci::Color("blue"));
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,3));
    vector<tuple<int,int>> locations;
    vector<Piece> removed;
    for(auto const& x : moves) {
      locations.push_back(x.first);
      removed.insert(removed.begin(), x.second.begin(), x.second.end());
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,2)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,4)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,5)) != locations.end());
    REQUIRE(removed[0].GetRow() == 3);
    REQUIRE(removed[0].GetCol() == 4);
  }

  SECTION("Get Valid Moves for blue piece with one possible double jump and one regular move") {
    Board board;
    board.SetPieceColor(4,5,ci::Color("black"));
    board.SetPieceAlive(1,4);
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(5,4));
    vector<tuple<int,int>> locations;
    vector<Piece> removed;
    for(auto const& x : moves) {
      locations.push_back(x.first);
      removed.insert(removed.begin(), x.second.begin(), x.second.end());
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,3)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(4,5)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(1,4)) != locations.end());
    REQUIRE(removed[0].GetRow() == 4);
    REQUIRE(removed[0].GetCol() == 5);
    REQUIRE(removed[1].GetRow() == 2);
    REQUIRE(removed[1].GetCol() == 5);
  }

  SECTION("Get Valid Moves for black piece with one possible double jump and one regular move") {
    Board board;
    board.SetPieceColor(3,4,ci::Color("blue"));
    board.SetPieceAlive(6,3);
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(2,3));
    vector<tuple<int,int>> locations;
    vector<Piece> removed;
    for(auto const& x : moves) {
      locations.push_back(x.first);
      removed.insert(removed.begin(), x.second.begin(), x.second.end());
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,2)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,4)) == locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(6,3)) != locations.end());
    REQUIRE(removed[1].GetRow() == 3);
    REQUIRE(removed[1].GetCol() == 4);
    REQUIRE(removed[0].GetRow() == 5);
    REQUIRE(removed[0].GetCol() == 4);
  }
}

TEST_CASE("Test Getting Valid Moves for kings") {
  SECTION("Test that blue king can move in all 4 directions") {
    Board board;
    board.SetPieceColor(4,3,ci::Color("blue"));
    board.SetPieceKing(4,3);
    board.SetPieceAlive(5,2);
    board.SetPieceAlive(5,4);
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(4,3));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,2)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,4)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(5,2)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(5,4)) != locations.end());
  }

  SECTION("Test that black king can move in all 4 directions") {
    Board board;
    board.SetPieceColor(4,3,ci::Color("black"));
    board.SetPieceKing(4,3);
    board.SetPieceAlive(5,2);
    board.SetPieceAlive(5,4);
    map<tuple<int,int>, vector<Piece>> moves = board.GetValidMoves(board.GetPiece(4,3));
    vector<tuple<int,int>> locations;
    for(auto const& x : moves) {
      locations.push_back(x.first);
    }
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,2)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(3,4)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(5,2)) != locations.end());
    REQUIRE(std::find(locations.begin(), locations.end(), make_tuple(5,4)) != locations.end());
  }
}