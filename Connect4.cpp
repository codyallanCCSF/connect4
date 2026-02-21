#include "constants.h"
#include <iostream>
#include <string>

// Builds and populates the game board
void initializeBoard(char board[][COLUMNS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      board[i][j] = EMPTY_SQUARE;
    }
  }
}

// Changes the grid to a string using newlines
std::string boardToString(char board[][COLUMNS]) {
  std::string result = "";
  for (size_t i = 0; i < ROWS; i++) {
    for (size_t j = 0; j < COLUMNS; j++) {
      result += board[i][j];
    }
    result += '\n';
  }
  return result;

}

// Drops a player's piece onto the game board
bool placePiece(Player player, int column, char board[][COLUMNS]) {
  if (column < 1 || column > static_cast<int>(COLUMNS)) {
    return false;
  }
  
  int colIndex = column - 1;
  char currentPiece = (player == PLAYER_ONE) ? PLAYER_ONE_PIECE : PLAYER_TWO_PIECE;

  for (int i = static_cast<int>(ROWS) - 1; i >= 0; i--) {
    if (board[i][colIndex] == EMPTY_SQUARE) {
      board[i][colIndex] = currentPiece;
      return true;
    }
  }
  return false;
}

// Executes the game loop until player opts out
void playGame(char board[][COLUMNS]) {
  bool playAgain = true;
  char response;

  while (playAgain) {
    std::cout << boardToString(board) << std::endl;

    std::cout << "Play again? (y/n): ";
    std::cin >> response;

    if (response == 'n' || response == 'N') {
      playAgain = false;
    }
  }
}
/*
bool isWin(Player player, char board[][COLUMNS])

bool isDraw(char board[][COLUMNS])
*/
