//
// Created by fkantere on 5/28/15.
//

#include "HeuristicStrategy.hpp"
#include "MoveCalculator.hpp"

Move HeuristicStrategy::calculate_next_move() {
  std::vector<Move> available_moves = MoveCalculator::get_possible_moves(situation_);
  Move m = available_moves[0];
  m.new_pos = situation_.players_[situation_.player_id_-1].pos_;
  return m;
}

void HeuristicStrategy::move_accepted() {

}

void HeuristicStrategy::move_rejected() {

}
