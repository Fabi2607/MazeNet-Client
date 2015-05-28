//
// Created by fkantere on 5/28/15.
//

#include "HeuristicStrategy.hpp"
#include "MoveCalculator.hpp"

Move HeuristicStrategy::calculate_next_move() {
  std::vector<Move> available_basic_moves = MoveCalculator::get_possible_moves(situation_);

  std::vector<std::pair<Move, GameSituation>> available_moves;

  // generiere mögliche Züge
  for(auto& move: available_basic_moves) {
    GameSituation cur_situation = situation_;
    cur_situation.perform_shift(move);

    std::vector<Position> positions = MoveCalculator::get_possible_positions(cur_situation);
    for(auto pos: positions) {
      Move new_m = move;
      new_m.new_pos = pos;
      cur_situation.setPlayerPos(pos);

      available_moves.push_back(std::make_pair(new_m, cur_situation));
    }
  }

  std::cout << "Calculated situations: " << available_basic_moves.size() << std::endl;
  std::cout << "Calculated moves: " << available_moves.size() << std::endl;


  // hier sollten moves und situations evaluiert werden
  Move m = available_moves[0].first;
  m.new_pos = situation_.players_[situation_.player_id_-1].pos_;
  return m;
}

void HeuristicStrategy::move_accepted() {

}

void HeuristicStrategy::move_rejected() {

}
