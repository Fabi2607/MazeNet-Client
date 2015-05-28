//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_GAMELOGIC_H
#define MAZENET_CLIENT_GAMELOGIC_H


class GameLogic {
 public:
  int getPlayer_id() const {
    return player_id_;
  }

  void setPlayer_id(int player_id) {
    player_id_ = player_id;
  }

 private:
  int player_id_;
};


#endif //MAZENET_CLIENT_GAMELOGIC_H
