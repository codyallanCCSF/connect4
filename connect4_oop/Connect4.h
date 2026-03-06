#ifndef CONNECT4_H
#define CONNECT4_H

#include "Player.h"

class Connect4 {

  // Constants for fixed array
  const size_t ROWS = 8;
  const size_t COLUMNS = 8;

  private:

    // Private variables
    char board[ROWS][COLUMNS];
    char player1Pieces;
    char player2Pieces;
    
    // Private helper functions
    void initializeBoard();
    bool isWinningPattern(int row, int col, int drow, int dcol, char piece) const;
    std::string getBoard() const;
  
  public:

    // Constructors
    Connect4();
    Connect4(int rows, int columns);
    Connect4(int rows, int columns, char player1pieces,
        char player2pieces);

    // Accessors
    bool isWin(const Player player) const;
    bool isDraw() const;

    // Mutator
    bool placePiece(Player player, int column);

    void playGame();
}

#endif

