//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_GAMELOGIC_H
#define MAZENET_CLIENT_GAMELOGIC_H


#include "Board.hpp"
#include "Player.hpp"

#include <set>
#include <messaging/MessageDispatcher.hpp>

class GameLogic {
 public:
  GameLogic() = default;
  int getPlayer_id() const {
    return player_id_;
  }

  void setPlayer_id(int player_id) {
    player_id_ = player_id;
  }

  Board board_ = Board();
  Card shiftCard_ = Card();
  int forbidden_row_ = -1;
  int forbidden_col_ = -1;
  Player players_[4];
  int treasure_ = -1;
  int player_count_ = -1;
  std::set<int> found_treasures_;
 private:
  int player_id_ = -1;
};


#endif //MAZENET_CLIENT_GAMELOGIC_H
