//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_HEURISTICSTRATEGY_H
#define MAZENET_CLIENT_HEURISTICSTRATEGY_H


#include "IPlayerStrategy.hpp"
#include "Move.hpp"

class HeuristicStrategy : public IPlayerStrategy {
 public:
  virtual Move calculate_next_move() override;

  virtual void move_accepted() override;

  virtual void move_rejected() override;
 private:
};


#endif //MAZENET_CLIENT_HEURISTICSTRATEGY_H
