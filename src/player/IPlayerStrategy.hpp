//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_IPLAYERSTRATEGY_H
#define MAZENET_CLIENT_IPLAYERSTRATEGY_H


#include "GameSituation.hpp"
#include "Move.hpp"

class IPlayerStrategy {
 public:
  virtual ~IPlayerStrategy();

  virtual Move calculate_next_move() = 0;

  virtual void move_accepted() = 0;
  virtual void move_rejected() = 0;

  GameSituation situation_ = GameSituation();
};


#endif //MAZENET_CLIENT_IPLAYERSTRATEGY_H
