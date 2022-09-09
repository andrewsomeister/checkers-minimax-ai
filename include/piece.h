#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H
#include "cinder/gl/gl.h"
namespace checkers {
class Piece {
 public:
  /**
    * Empty constructor for piece
   */
  Piece();
  /**
    * Constructor for Piece with a row, column, and color
    *
    * @param row Row
    * @param col Column
    * @param color color of piece
   */
  Piece(int row, int col, cinder::ColorT<float> color, bool isAlive);
  /**
    * Returns the pixel position of the checker board
   */
  void CalculatePosition();
  /**
    * Makes the Piece a King
   */
  void MakeKing();
  /**
    * Displays the piece
   */
  void Display();
  /**
  * Moves the piece to a new spot
   */
  void Move(int row, int col);

  // GETTERS
  int GetCol();
  int GetRow();
  bool IsAlive();
  cinder::ColorT<float> GetColor();
  bool IsKing();

  // SETTERS
  void SetAlive(bool alive);
  void SetColor(cinder::ColorT<float> color);

 private:
  // private variables storing information about the piece such as row, column, king status, and position
  bool is_king_;
  bool is_alive_;
  int row_;
  int col_;
  cinder::ColorT<float> color_;
  glm::vec2 position_;

  // constant variables denoting the square size pf the board and the padding of the circle
  const static int kSquareSize = 100;
  constexpr const static float kCircleSize = 20;
  const static int kPadding = 5;
};
}
#endif //CHECKERS_PIECE_H