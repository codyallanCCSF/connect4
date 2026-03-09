#include <iostream>
#include "Connect4.h"
#include <string>

// Constructors

// Creates 8x8 board
Connect4::Connect4() {
  this->player1Pieces = 'x';
  this->player2Pieces = 'o';
  this->initializeBoard();
}

// Creates board with specified dimensions
Connect4::Connect4(int rows, int columns) {
  this->actualRows = rows;
  this->actualColumns = columns;
  this->player1Pieces = 'x';
  this->player2Pieces = 'o';
  this->initializeBoard();
}

// Creates board with specified dimensions and pieces
Connect4::Connect4(int rows, int columns,
    char player1Pieces, char player2Pieces) {

  this->actualRows = rows;
  this->actualColumns = columns;
  this->player1Pieces = player1Pieces;
  this->player2Pieces = player2Pieces;
  this->initializeBoard();
}

// Private functions

// Builds default board
void Connect4::initializeBoard() {
  for (size_t i = 0; i < actualRows; i++) {
    for (size_t j = 0; j < actualColumns; j++) {
      this->board[i][j] = '-';
    }
  }
}

// Creates general structure for finding winning patterns
bool Connect4::isWinningPattern(int row, int col,
    int dRow, int dCol, char piece) const {

  for (int i = 0; i < WIN_COUNT; i++) {

    int targetRow = (i * dRow) + row;
    int targetCol = (i * dCol) + col;

    if (targetRow < 0 || targetRow >= actualRows ||
        targetCol < 0 || targetCol >= actualColumns) {
      return false;
    }

    if (this->board[targetRow][targetCol] != piece) {
      return false;
    }
  }
  return true;
}

// Public methods

// Drops player piece in selected column
bool Connect4::placePiece(Player player, int column) {
  if (column < 1 || column > actualColumns) return false;  
  
  int colIndex = column - 1;

  char currentPiece = (player == PLAYER_ONE)
                      ? this->player1Pieces
                      : this->player2Pieces;
  
  for (int i = actualRows - 1; i >= 0; i--) {
    if (board[i][colIndex] == EMPTY_SQUARE) {
      board[i][colIndex] = currentPiece;
      return true;
    }
  }
  return false;
}

// Checks for a win using isWinningPattern()
bool Connect4::isWin(const Player player) const {

  char piece = (player == PLAYER_ONE) 
                ? this->player1Pieces
                : this->player2Pieces;

  for (size_t row = 0; row < actualRows; row++){
    for (size_t col = 0; col < actualColumns; col++) {

      if (this->board[row][col] == piece) {

        // Horizontal
        if (isWinningPattern(row, col, 0, 1, piece)) {
          return true;
        }
        // Vertical
        if (isWinningPattern(row, col, 1, 0, piece)) {
          return true;
        }
        // Descending diagonal
        if (isWinningPattern(row, col, 1, 1, piece)) {
          return true;
        }
        // Ascending diagonal
        if (isWinningPattern(row, col, -1, 1, piece)) {
          return true;
        }      
      }
    }
  }
  return false;
}

// Determines a full board (draw)
bool Connect4::isDraw() const {
  for (size_t j = 0; j < actualColumns; j++) {
    if (this->board[0][j] == EMPTY_SQUARE) return false; 
  }
  return true;
}

// Prints board as a string
std::string Connect4::getBoard() const {
  std::string result = "";
  for (size_t i = 0; i < actualRows; i++) {
    for (size_t j = 0; j < actualColumns; j++) {
      result += this->board[i][j];
    }
    result += '\n';
  }
  return result;
}

// Runs game loop
void Connect4::playGame() {

  bool playAgain = true;
  char replayResponse;

  while (playAgain) {

    this->initializeBoard();

    int playerNum;
    int columnChoice;

    bool keepPlaying = true;
    bool isPlayerOne = true;

    while (keepPlaying) {

      Player currentPlayer = (isPlayerOne) 
                      ? PLAYER_ONE 
                      : PLAYER_TWO;
      playerNum = (isPlayerOne) ? 1 : 2;

      std::cout << "\n" << "Player " << playerNum <<  "\n" <<  std::endl;
      std::cout << this->getBoard() << std::endl;

      std::cout 
        << "Player " 
        << playerNum 
        << ", please enter a column number (1 - " 
        << actualColumns 
        << "): " 
        << std::endl;
      std::cin >> columnChoice;          

       if (this->placePiece(currentPlayer, columnChoice)) {
          
         if (this->isWin(currentPlayer)) {

           std::cout << (currentPlayer == PLAYER_ONE 
                        ? PLAYER_ONE_WIN_MESSAGE
                        : PLAYER_TWO_WIN_MESSAGE);
            
           std::cout << '\n' << this->getBoard() << std::endl;
           keepPlaying = false;
         }

         else if (this->isDraw()) {

           std::cout << DRAW_MESSAGE << std::endl;
           std::cout << '\n' << this->getBoard() << std::endl;
           keepPlaying = false;          
         }         
         else {

           isPlayerOne = !isPlayerOne;
         }
       } else {

         std::cout << BAD_COLUMN_MESSAGE << std::endl;
       }
     }  

    if (playAgain) {
      std::cout << "Play again? (y/n): " << std::endl;
      std::cin >> replayResponse;

      if (replayResponse != 'y') {
        std::cout << "Thanks for playing!" << std::endl;
        playAgain = false;
      }
    }     
  }
}

