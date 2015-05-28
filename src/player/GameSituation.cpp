//
// Created by fkantere on 5/28/15.
//

#include "GameSituation.hpp"

void GameSituation::perform_shift(Move m) {
  // Spieler betritt Spielfeld
  for(int i = 1; i<=4;++i) {
    if(shiftCard_.hasPlayer(i)) {
      players_[i-1].pos_ = m.shift_pos;
    }
  }

  shiftCard_ = board_.insert_card(m.shift_card, m.shift_pos);

  // Spieler verlässt Spielfeld
  for(int i = 1; i<=4;++i) {
    if(shiftCard_.hasPlayer(i)) {
      players_[i-1].pos_ = {-1,-1};
    }
  }
}

void GameSituation::setPlayerPos(Position new_pos) {
  Position old_pos = players_[player_id_-1].pos_;
  if(old_pos.row != -1)
    board_.cards_[old_pos.row][old_pos.col].removePlayer(player_id_);

  players_[player_id_-1].pos_ = new_pos;
  if(new_pos.row != -1)
    board_.cards_[new_pos.row][new_pos.col].setPlayer(player_id_);
}
