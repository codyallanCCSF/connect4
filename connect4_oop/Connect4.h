#ifndef CONNECT4_H
#define CONNECT4_H

#include "Player.h"
#include <string>

class Connect4 {

  private:
    
    // Constants for fixed array    
    static const size_t MAX_ROWS = 20;
    static const size_t MAX_COLUMNS = 20;
    static const size_t WIN_COUNT = 4;
    static const char EMPTY_SQUARE = '-';

    // Constants for game announcements
    const std::string PLAYER_ONE_WIN_MESSAGE = "Player 1 has won!";
    const std::string PLAYER_TWO_WIN_MESSAGE = "Player 2 has won!";
    const std::string DRAW_MESSAGE = "Game ended by draw";
    const std::string BAD_COLUMN_MESSAGE = "Invalid column";

    // Private variables
    char board[MAX_ROWS][MAX_COLUMNS];
    int actualRows;
    int actualColumns;
    char player1Pieces;
    char player2Pieces;
    
    // Private helper functions
    void initializeBoard();
    bool isWinningPattern(int row, int col, int drow, int dcol, char piece) const;
  
  public:

    // Constructors
    Connect4();
    Connect4(int rows, int columns);
    Connect4(int rows, int columns, char player1pieces,
        char player2pieces);

    // Accessors
    bool isWin(const Player player) const;
    bool isDraw() const;
    std::string getBoard() const;

    // Mutator
    bool placePiece(Player player, int column);

    void playGame();
};

#endif

