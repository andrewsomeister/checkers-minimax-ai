#pragma once
#ifndef CHECKERS_APP_H_
#define CHECKERS_APP_H_

#include "board.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace checkers {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class CheckersApp : public ci::app::App {
 public:
  CheckersApp();

  void draw() override;
  void mouseDown(cinder::app::MouseEvent event) override;
  void mouseDrag(cinder::app::MouseEvent event) override;
  void mouseUp(cinder::app::MouseEvent event) override;
  /**
  * Uses mouse down to select a piece in a row or column
  */
  bool SelectPiece(int row, int col);

  /**
  * Uses mousedown event to move a piece to a player's desired location
  */
  bool MovePiece(int row, int col);

  /**
  * Draws the valid moves for the player's selected piece
  */
  void DrawValidMoves(map<tuple<int,int>, vector<Piece>> moves);

  /**
  * Changes it to the next player's turn
  */
  void NextTurn();

  /**
  * Calculates computers best move
  */
  Board ComputerMove();

  void DrawUI();
  void RestartGame();
  bool IsWithinButtonBounds(const glm::vec2& pos);
  void UpdateSliderPosition(const glm::vec2& pos);

 private:
  //constants for setting up the window and board
  const int kWindowSize = 1000;
  const int kSquareSize = 100;

  //private variables denoting key features of the app such as a board,
  // whether a piece is currently selected, and whose turn it is
  Board board_;
  bool selected_;
  cinder::ColorT<float> turn_;
  Piece selected_piece_;
  map<tuple<int,int>, vector<Piece>> valid_moves_;
  std::string rules_text_;
  ci::Rectf restart_button_;
  ci::Rectf slider_bar_;
  ci::Rectf slider_handle_;
  bool is_dragging_slider_ = false;
  int ai_lookahead_ = 4; // Default lookahead depth
  std::vector<float> slider_snap_points_;
  void SnapToClosestValue();
  bool isAiTurn = false; // Flag to indicate it's AI's turn
  bool aiDelayActive = false; // Flag to indicate the delay is active
  double aiDelayStartTime; // Time when the delay started
  const double aiMoveDelay = 1.0; // Delay duration in seconds
};
}  // namespace checkers
#endif //CHECKERS_APP_H_
