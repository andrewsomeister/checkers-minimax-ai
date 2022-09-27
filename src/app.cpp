#include <app.h>
#include <minimax.h>
using namespace std;

namespace checkers {

CheckersApp::CheckersApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  turn_ = ci::Color("blue");
  selected_ = false;
}

void CheckersApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  board_.Display();
  DrawValidMoves(valid_moves_);
  if (turn_ == ci::Color("black")) {
    board_ = ComputerMove();
  }
}

void CheckersApp::mouseDown(cinder::app::MouseEvent event) {
  if(event.isLeft()) {
    glm::vec2 mouse_loc = event.getPos();
    int row = (int) mouse_loc[1] / kSquareSize;
    int col = (int) mouse_loc[0] / kSquareSize;
    SelectPiece(row, col);
  }
}

bool CheckersApp::SelectPiece(int row, int col) {
  if(selected_) {
    bool moved = MovePiece(row, col);
    if(!moved) {
      valid_moves_ = {};
      selected_ = false;
      SelectPiece(row, col);
    }
  }
  Piece piece = board_.GetPiece(row, col);
  if (piece.IsAlive() && piece.GetColor() == turn_) {
    selected_piece_ = piece;
    selected_ = true;
    valid_moves_ = board_.GetValidMoves(selected_piece_);
    return true;
  }
  return false;
}

bool CheckersApp::MovePiece(int row, int col) {
  Piece piece = board_.GetPiece(row, col);
  if (selected_ && !piece.IsAlive() && (valid_moves_.find(make_tuple(row, col)) != valid_moves_.end())) {
    board_.Move(selected_piece_, row, col);
    vector<Piece> skipped = valid_moves_[make_tuple(row, col)];
    if (!skipped.empty()) {
      board_.Remove(skipped);
    }
    NextTurn();
  } else {
    return false;
  }
  return true;
}

void CheckersApp::NextTurn() {
  valid_moves_ = {};
  if (turn_ == ci::Color("blue")) {
    turn_ = ci::Color("black");
  } else {
    turn_ = ci::Color("blue");
  }
}

void CheckersApp::DrawValidMoves(map<tuple<int,int>, vector<Piece>> moves) {
  for(auto const& x : moves) {
    int row = std::get<0>(x.first);
    int col = std::get<1>(x.first);
    glm::vec2 position;
    position[0] = (float) kSquareSize * col + kSquareSize / 2;
    position[1] = (float) kSquareSize * row + kSquareSize / 2;
    ci::gl::color(ci::Color("yellow"));
    ci::gl::drawSolidCircle(position, 20);
  }
}
Board CheckersApp::ComputerMove() {
  NextTurn();
  return std::get<0>(Minimax::ReturnBestMove(board_, 4, true));
}
}  // namespace checkers\