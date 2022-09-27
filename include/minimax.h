#ifndef CHECKERS_INCLUDE_MINIMAX_H_
#define CHECKERS_INCLUDE_MINIMAX_H_
#include <vector>
#include "board.h"
using namespace std;
namespace checkers {
class Minimax {
 public:
  /**
  * Moves a piece to a new row and column
  *
  * @param Board board which needs to be analyzed by the ai
  * @param depth to which the ai will analyze the board
  * @param ai_turn whether the recursive algorithm will be an the player turn or ai turn
   */
  static tuple<Board, double> ReturnBestMove(Board board, int depth,
                                            bool ai_turn);

  /**
    * Simulates a move for the minimax algorithm
    *
    * @param Piece piece which needs the move to be simulated
    * @param moveRow, row to whih piece is being moved to
    * @param moveCol, col to which pieve is being moved to
    * @param skip, whether or not anything has been skipped or not
   */
  static Board SimulateMove(Board board, Piece piece, int move_row,
                            int move_col, vector<Piece> skipped);

  /**
    * Returns all the possible boards, from a certain board
    *
    * @param Board board which is analyzed
    * @param color of which player we are getting all the boards for
   */
  static vector<Board> GetAllBoards(Board board, cinder::ColorT<float> color);
};
}
#endif  // CHECKERS_INCLUDE_MINIMAX_H_