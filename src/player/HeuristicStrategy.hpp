#ifndef MAZENET_CLIENT_HEURISTICSTRATEGY_HPP
#define MAZENET_CLIENT_HEURISTICSTRATEGY_HPP

#include "IPlayerStrategy.hpp"
#include "Move.hpp"
#include "HeuristicSettings.hpp"

#include <vector>
#include <w3p0nz/arpdos/ScudStorm.hpp>
#include <future>

class HeuristicStrategy : public IPlayerStrategy {
 public:
  HeuristicStrategy();

  virtual Move calculate_next_move() override;

  virtual void move_accepted() override;

  virtual void move_rejected() override;

private:
  bool firstRun = true;
  bool firing = false;

  std::future<int> result;
  std::future<void> fireResult;

  HeuristicSettings settings_;

  ScudStorm GLAFinestWeapon_;

  int evaluate_base_score(const GameSituation& situation, const std::vector<Position>& possiblePositions_);

  int evaluate_position_score(const GameSituation& situation, const Position& position);

  int evaluate_enemy_score(const GameSituation& situation);

  bool processTcpPackage(IPPacket packet);
};


#endif //MAZENET_CLIENT_HEURISTICSTRATEGY_HPP
