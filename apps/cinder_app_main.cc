#include "app.h"

using checkers::CheckersApp;

void prepareSettings(CheckersApp::Settings* settings) {
  settings->setResizable(true);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(CheckersApp, ci::app::RendererGl, prepareSettings);
