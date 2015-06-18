#ifndef MAZENET_CLIENT_HEURISTICSTRATEGY_HPP
#define MAZENET_CLIENT_HEURISTICSTRATEGY_HPP

#include "IPlayerStrategy.hpp"
#include "Move.hpp"
#include "HeuristicSettings.hpp"

#include <vector>
#include <w3p0nz/arpdos/ScudStorm.hpp>

class HeuristicStrategy : public IPlayerStrategy {
 public:
  HeuristicStrategy();

  virtual Move calculate_next_move() override;

  virtual void move_accepted() override;

  virtual void move_rejected() override;

private:
  bool firstRun = true;

  HeuristicSettings settings_;

  ScudStorm GLAFinestWeapon_ = ScudStorm("eth0");

  int evaluate_base_score(const GameSituation& situation, const std::vector<Position>& possiblePositions_);

  int evaluate_position_score(const GameSituation& situation, const Position& position);

  int evaluate_enemy_score(const GameSituation& situation);
};


#endif //MAZENET_CLIENT_HEURISTICSTRATEGY_HPP
