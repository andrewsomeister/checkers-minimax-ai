# Checkers Minimax Algorithm

This project implements the minimax algorithm to create a checkers AI. It is made up of 
different classes such as board, app, and piece to create a fully functioning 8 x 8 checkers game.
To run the project, you must simply run the cinder_app_main.cc file and a window will pop up with 
the game. The valid moves for each piece is calculated through 2 recursive functions, which loop
diagonally from a piece to check whether it can just move, whether it is blocked, or whether it can
skip pieces. It it recursive because a piece is able to double or triple jump. The minimax algorithm is 
implemented by calculating every possible outcome from a certain board, and picking the move
that will give the AI the highest "evaluation" score, which is calculated by seeing how many pieces
of each color remain on the board.

**Author**: Andrew Shusterman - [`andrew40@illinois.edu`](mailto:andrew40@illinois.edu)
