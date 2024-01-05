#include <app.h>
#include <minimax.h>
#include <algorithm> 
#include "cinder/Text.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
using namespace std;
using namespace ci;
using namespace ci::app;

namespace checkers {

CheckersApp::CheckersApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  turn_ = ci::Color("blue");
  selected_ = false;

  rules_text_ = "Basic Rules\n1. You are not forced to take pieces\n2. Kings can move and take backwards\n3. Adjust slider higher for increased difficulty";
  restart_button_ = Rectf(400, 850, 600, 920); // Adjust position and size as needed
  

  slider_bar_ = ci::Rectf(850, 50, 900, 250); // Adjust the position and size
  slider_handle_ = ci::Rectf(845, 45, 905, 55); // Initial handle position
  slider_snap_points_ = { 50, 100, 150, 200, 250 }; // Y-coordinates for snap points

}

void CheckersApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);
  board_.Display();
  DrawValidMoves(valid_moves_);
  DrawUI();
  if (turn_ == ci::Color("black")) {
      if (isAiTurn && aiDelayActive) {
          if (getElapsedSeconds() - aiDelayStartTime >= aiMoveDelay) {
              aiDelayActive = false; // End delay
              // Perform AI move
              board_ = ComputerMove();
              isAiTurn = false; // Switch turn back to player
          }
      }
    //board_ = ComputerMove();
  }
}
void CheckersApp::DrawUI() {
    // Draw the title centered above the board
    gl::drawString("Checkers Minimax AI Project", vec2(50, 30), Color("white"), Font("Arial", 50));
    gl::color(Color("white"));

    // Rules text using TextBox
    ci::TextBox rulesBox;
    rulesBox.setFont(Font("Arial", 20));
    rulesBox.setText(rules_text_);
    rulesBox.setSize(glm::ivec2(350, 250));
    rulesBox.setColor("white");
    auto rulesSurface = rulesBox.render();
    ci::gl::Texture2dRef rulesTexture = ci::gl::Texture2d::create(rulesSurface);
    gl::draw(rulesTexture, vec2(600, 10));

    // Restart button
    restart_button_ = Rectf(400, 910, 600, 960);
    gl::color(Color("white"));
    gl::drawSolidRect(restart_button_);
    gl::drawStringCentered("Restart", vec2(500,925), Color("black"), Font("Arial", 30));

    // AI lookahead slider text using TextBox
    gl::drawString("AI Difficulty", vec2(10, 350), Color("white"), Font("Arial", 20));

    gl::drawString("1", vec2(5, 390), Color("white"), Font("Arial", 20));
    gl::drawString("2", vec2(5, 440), Color("white"), Font("Arial", 20));
    gl::drawString("3", vec2(5, 490), Color("white"), Font("Arial", 20));
    gl::drawString("4", vec2(5, 540), Color("white"), Font("Arial", 20));
    gl::drawString("5", vec2(5, 590), Color("white"), Font("Arial", 20));

    // Slider bar and handle
    slider_bar_ = ci::Rectf(25, 400, 75, 600);
    slider_handle_ = ci::Rectf(20.0f, 395.0f + static_cast<float>(ai_lookahead_-1) * 50.0f, 80.0f, 405.0f + static_cast<float>(ai_lookahead_-1) * 50.0f);
    slider_snap_points_ = { 400, 450, 500, 550, 600 };
    gl::color(ci::Color("gray"));
    gl::drawSolidRect(slider_bar_);
    gl::color(ci::Color("blue"));
    gl::drawSolidRect(slider_handle_);
}


void CheckersApp::mouseDown(MouseEvent event) {

    int offset = 100;
    if (event.isLeft()) {
        vec2 mouse_loc = event.getPos();
        if (restart_button_.contains(mouse_loc)) {
            RestartGame();
        }
        else if (slider_handle_.contains(mouse_loc)) {
            is_dragging_slider_ = true;
        }
        else {
            int row = static_cast<int>((mouse_loc.y - 100.0) / kSquareSize);
            int col = static_cast<int>((mouse_loc.x - 100.0) / kSquareSize);

            if (row >= 0 && row < 8 && col >= 0 && col < 8) {
                SelectPiece(row, col);
            }
        }
    }
}

void CheckersApp::mouseDrag(ci::app::MouseEvent event) {
    if (is_dragging_slider_) {
        float newY = std::clamp(static_cast<float>(event.getY()), slider_bar_.y1, slider_bar_.y2);
        slider_handle_.offset(ci::vec2(0, newY - slider_handle_.getCenter().y));
        SnapToClosestValue();
    }
}

void CheckersApp::mouseUp(ci::app::MouseEvent event) {
    if (is_dragging_slider_) {
        is_dragging_slider_ = false;
        SnapToClosestValue();
    }
}

void CheckersApp::SnapToClosestValue() {
    float closest_distance = std::numeric_limits<float>::max();
    float closest_point = slider_snap_points_[0];
    for (float point : slider_snap_points_) {
        float distance = std::abs(point - slider_handle_.getCenter().y);
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_point = point;
        }
    }
    slider_handle_.offset(ci::vec2(0, closest_point - slider_handle_.getCenter().y));

    // Update ai_lookahead_ based on the position of the handle
    ai_lookahead_ = static_cast<int>((closest_point - static_cast<int>(slider_bar_.y1)) / 50) + 1;
}

void CheckersApp::RestartGame() {
    // Reset the game state
    board_ = Board();
    selected_ = false;
    turn_ = Color("blue");
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

  if (turn_ == ci::Color("black")) {
      isAiTurn = true;
      aiDelayActive = true;
      aiDelayStartTime = getElapsedSeconds();
  }
}



void CheckersApp::DrawValidMoves(map<tuple<int,int>, vector<Piece>> moves) {
  for(auto const& x : moves) {
    int row = std::get<0>(x.first);
    int col = std::get<1>(x.first);
    glm::vec2 position;
    position[0] = 100 + (float) kSquareSize * col + kSquareSize / 2;
    position[1] = 100 + (float) kSquareSize * row + kSquareSize / 2;
    ci::gl::color(ci::Color("yellow"));
    ci::gl::drawSolidCircle(position, 20);
  }
}
Board CheckersApp::ComputerMove() {
  NextTurn();
  return std::get<0>(Minimax::ReturnBestMove(board_, ai_lookahead_, true));
}
}  // namespace checkers\
