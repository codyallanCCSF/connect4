#include "Connect4.h"
#include "constants.h"

int main(){
  Connect4 game(ROWS, COLUMNS, PLAYER_ONE_PIECE, PLAYER_TWO_PIECE);

  game.playGame();
  return 0;

}
