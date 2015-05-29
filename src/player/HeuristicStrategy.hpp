//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_HEURISTICSTRATEGY_H
#define MAZENET_CLIENT_HEURISTICSTRATEGY_H

#include "IPlayerStrategy.hpp"
#include "Move.hpp"
#include "HeuristicSettings.hpp"

#include <vector>

class HeuristicStrategy : public IPlayerStrategy {
 public:
  virtual Move calculate_next_move() override;

  virtual void move_accepted() override;

  virtual void move_rejected() override;
 private:

  HeuristicSettings settings_;
  int evaluate_base_score(const GameSituation& situation, const std::vector<Position>& possiblePositions_);
  int evaluate_position_score(const GameSituation& situation, const Position& position);
};


#endif //MAZENET_CLIENT_HEURISTICSTRATEGY_H
