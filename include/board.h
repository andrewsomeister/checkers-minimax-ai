#ifndef CHECKERS_BOARD_H_
#define CHECKERS_BOARD_H_
#include <vector>
#include "piece.h"
namespace checkers {
using namespace std;
class Board {
 public:
  /**
  * Constructs an 8x8 board
   */
  Board();

  /**
  * Draws The Squares when displaying the board
   */
  void DrawSquares();

  /**
  * Evaluate the board's "score" to be used for the minimax algorithm
   *
   * @return evaluation score
   */
  double Evaluate();

  /**
  * Moves a piece to a new row and column
  *
  * @param piece which needs to be moved
  * @param row Row
  * @param col Column
   */
  void Move(Piece &piece, int row, int col);

  /**
  * Helper method to create the board by looping through rows and columns
   * to create the pieces on the board
   */
  void CreateBoard();

  /**
  * Displays the board and pieces
   */
  void Display();

  /**
  * Checks the board and determines whether or not there is a winner
   */
  bool CheckWinner();

  /**
  * Removes a vector of pieces used when pieces are captured
  *
  * @param pieces
   */
  void Remove(std::vector<Piece> pieces);

  /**
  * Returns the valid moves for a certain piece by using helper methods below
  *
  * @param Piece for which we are getting the valid moves from
  * @return map<tuple<int,int>, vector<Piece>> map with row col and valid move
  * and a vector of any pieces that are taken with that move
   */
  map<tuple<int, int>, vector<Piece>> GetValidMoves(Piece piece);

  /**
  * From a given row and column, traverses diagonally (left) up or down and determines whether the piece is able to move once, skip a piece, or not move at all. If a piece is able to jump, it then calls for CheckMovesLeft and CheckMoves Right recursively to check if it can double jump
  *
  * @param int start, the start row it should check
  * @param int end, the last row it should check
  * @param int step, the value of the iterator going through the for loop
  * @param cinder::ColorT<float> color, color of the piece it is checking
  * @param int col, column that it starts checking
  * @param skipped, any pieces that have already been skipped
  * @return map<tuple<int,int>, vector<Piece>> map with row col and valid move
  * and a vector of any pieces that are taken with that move
   */
  map<tuple<int, int>, vector<Piece>> CheckMovesLeft(
      int start, int end, int step, cinder::ColorT<float> color, int col,
      std::vector<Piece> skipped = {});

  /**
  * From a given row and column, traverses diagonally (right) up or down and determines whether the piece is able to move once, skip a piece, or not move at all. If a piece is able to jump, it then calls for CheckMovesLeft and CheckMoves Right recursively to check if it can double jump
  *
  * @param int start, the start row it should check
  * @param int end, the last row it should check
  * @param int step, the value of the iterator going through the for loop
  * @param cinder::ColorT<float> color, color of the piece it is checking
  * @param int col, column that it starts checking
  * @param skipped, any pieces that have already been skipped
  * @return map<tuple<int,int>, vector<Piece>> map with row col and valid move
  * and a vector of any pieces that are taken with that move
   */
  map<tuple<int, int>, vector<Piece>> CheckMovesRight(
      int start, int end, int step, cinder::ColorT<float> color, int col,
      std::vector<Piece> skipped = {});

  // GETTERS
  vector<Piece> GetPieces(cinder::ColorT<float> color);
  Piece GetPiece(int row, int col);

  // SETTERS
  void SetPieceColor(int row, int col, cinder::ColorT<float> color);
  void SetPieceAlive(int row, int col);
  void SetPieceKing(int row, int col);

 private:
  // private member variables denoting how many of each piece and/or kings are left
  vector<vector<Piece>> board_;
  double blue_left_;
  double black_left_;
  double blue_kings_;
  double black_kings_;

  // constants for determining board size
  const static int kRows = 8;
  const static int kCols = 8;
  const static int kSquareSize = 100;
};
}
#endif //CHECKERS_BOARD_H_