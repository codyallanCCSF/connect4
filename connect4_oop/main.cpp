#include "constants.h"
#include <iostream>
#include <string>

void playGame(char board[][COLUMNS]);
void initializeBoard(char board[][COLUMNS]);
std::string boardToString(char board[][COLUMNS]);


int main(){
  char board[ROWS][COLUMNS];

  initializeBoard(board);

  playGame(board);
  return 0;

}
