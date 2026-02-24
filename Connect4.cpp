#include "constants.h"
#include <iostream>
#include <string>

// Builds and populates the game board
void initializeBoard(char board[][COLUMNS]) {
  for (size_t i = 0; i < ROWS; i++) {
    for (size_t j = 0; j < COLUMNS; j++) {
      board[i][j] = EMPTY_SQUARE;
    }
  }
}

// Changes the grid to a string delimited with newlines
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
  if (column < 1 || column > COLUMNS) {
    return false;
  }
  
  // Adjusts column input for zero indexing
  int colIndex = column - 1;

  // Assigns piece char depending on current player
  char currentPiece = (player == PLAYER_ONE) ? PLAYER_ONE_PIECE : PLAYER_TWO_PIECE;
  
  // Uses int instead of size_t for backwards count
  for (int i = ROWS - 1; i >= 0; i--) {
    if (board[i][colIndex] == EMPTY_SQUARE) {
      board[i][colIndex] = currentPiece;
      return true;
    }
  }
  return false;
}

// Separates winning pattern math from isWin for readability
// Uses ints instead of size_t to prevent unsigned overflow
bool isWinningPattern (int row, int col, int dRow, int dCol, char piece, char board[][COLUMNS]) {

  // Loops a maximum of WIN_COUNT (4) times
  for (int i = 0; i < WIN_COUNT; i++) {

    /* 
       Uses slope-intercept form (y = mx + b)
       to calculate row and column
       displacement:

       y = targetRow, m = i, x = dRow/Col, b = row/col

       */
    int targetRow = (i * dRow) + row;
    int targetCol = (i * dCol) + col;

    // Returns false if targetRow/Col is out of range
    if (targetRow < 0 || targetRow >= ROWS ||
        targetCol < 0 || targetCol >= COLUMNS) {
      return false;
    }

    // Returns false if piece at targetRow/Col doesn't match currentPlayer
    if (board[targetRow][targetCol] != piece) {
      return false;
    }
  }
  return true;
}

// Calls isWinningPattern with corresponding inputs for each pattern
bool isWin(Player player, char board[][COLUMNS]) {

  // Assigns piece X or O depending on player input
  char piece = (player == PLAYER_ONE) ? PLAYER_ONE_PIECE : PLAYER_TWO_PIECE;

  for (size_t row = 0; row < ROWS; row++){
    for (size_t col = 0; col < COLUMNS; col++) {

      // Only checks current player's pieces
      if (board[row][col] == piece) {

        // Horizontal
        if (isWinningPattern(row, col, 0, 1, piece, board)) {
          return true;
        }
        // Vertical
        if (isWinningPattern(row, col, 1, 0, piece, board)) {
          return true;
        }
        // Descending diagonal
        if (isWinningPattern(row, col, 1, 1, piece, board)) {
          return true;
        }
        // Ascending diagonal
        if (isWinningPattern(row, col, -1, 1, piece, board)) {
          return true;
        }      
      }
    }
  }
  return false;
}

// Returns false if any top row space is empty
bool isDraw(char board[][COLUMNS]) {
  for (size_t j = 0; j < COLUMNS; j++) {
    if (board[0][j] == EMPTY_SQUARE) {
      return false;
    }
  }
  return true;
}

// Executes the game loop until player opts out
void playGame(char board[][COLUMNS]) {
  
  // Initializes flag for outer loop and replay variable
  bool playAgain = true;
  char replayResponse;

  // Outer loop start
  while (playAgain) {

    initializeBoard(board);

    // Initializes inner loop variables
    Player currentPlayer;
    int playerNum;
    int columnChoice;

    // Initializes flags for inner loop and currentPlayer
    bool keepPlaying = true;
    bool isPlayerOne = true;

    // Inner loop start
    while (keepPlaying) {

      // Changes currentPlayer depending on flag state  
      currentPlayer = (isPlayerOne) ? PLAYER_ONE : PLAYER_TWO;

      // Assigns playerNum depending on currentPlayer
      playerNum = (isPlayerOne) ? 1 : 2;

      // Announces currentPlayer and prints current board
      std::cout << "\n" << "Player " << playerNum <<  "\n" <<  std::endl;
      std::cout << boardToString(board) << std::endl;

      // Prompts player for next move
      std::cout 
        << "Player " 
        << playerNum 
        << ", please enter a column number (1 - " 
        << COLUMNS 
        << "): " 
        << std::endl;
      std::cin >> columnChoice;          

       // Checks if move was successful
       if (placePiece(currentPlayer, columnChoice, board)) {
          
         // Checks for winning move
         if (isWin(currentPlayer, board)) {

           // Announces winner as currentPlayer
           std::cout << (currentPlayer == PLAYER_ONE 
               ? PLAYER_ONE_WIN_MESSAGE : PLAYER_TWO_WIN_MESSAGE);
            
           // Prints final board and exits inner loop
           std::cout << '\n' << boardToString(board) << std::endl;
           keepPlaying = false;
         }

         // Checks for a full board
         else if (isDraw(board)) {

           // Exits inner loop if board is full
           std::cout << DRAW_MESSAGE << std::endl;
           std::cout << '\n' << boardToString(board) << std::endl;
           keepPlaying = false;          
         }         
         else {

           // Switches players if game continues
           isPlayerOne = !isPlayerOne;
         }
       } else {

         // Prints message and repeats inner loop if input invalid
         std::cout << BAD_COLUMN_MESSAGE << std::endl;
       }
     }  

    // Repeats game only on 'y' input
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

