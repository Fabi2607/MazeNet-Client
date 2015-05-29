//
// Created by fkantere on 5/28/15.
//

#include <util/logging/Log.hpp>
#include "HeuristicStrategy.hpp"
#include "MoveCalculator.hpp"

Move HeuristicStrategy::calculate_next_move() {
  mazenet::util::logging::Log logger("heuristic");
  Move best_move;
  int best_score = 0;
  logger.log() << "Evaluating: " << situation_.board_
  << "\nShift Card: " << situation_.shiftCard_
  << "\nPlayer Pos: " << "R: " << situation_.players_[situation_.player_id_-1].pos_.row
                                 << " C: " << situation_.players_[situation_.player_id_-1].pos_.col << logger.end();

  std::vector<Move> available_basic_moves = MoveCalculator::get_possible_moves(situation_);

  // generiere mögliche Züge
  for(auto& move: available_basic_moves) {
    GameSituation cur_situation = situation_;
    cur_situation.perform_shift(move);

    std::vector<Position> positions = MoveCalculator::get_possible_positions(cur_situation);

    logger.log() << "Choice: \n" << cur_situation.board_
     << "\nPositions: " <<logger.end() ;

    int base_score = evaluate_base_score(cur_situation, positions);

    Move current_move = move;
    for(auto& pos: positions) {

      current_move.new_pos = pos;

      int actual_score = base_score;
      actual_score += evaluate_position_score(cur_situation, pos);
      logger.log() << "\nR: "<<  pos.row << " C: " << pos.col
       << " Score: " << actual_score << logger.end();

      if(actual_score > best_score) {
        best_move = current_move;
        best_score = actual_score;
      }
    }
  }

  std::cout << "Calculated situations: " << available_basic_moves.size() << std::endl;

  return best_move;
}

void HeuristicStrategy::move_accepted() {

}

void HeuristicStrategy::move_rejected() {

}

int HeuristicStrategy::evaluate_base_score(const GameSituation& situation, const std::vector<Position>& possiblePositions) {
  int score = 0;

  // base score for reachable fields
  score += possiblePositions.size()*settings_.reachableFieldValue;

  for(auto& pos: possiblePositions) {
    auto& cur_card = situation.board_.cards_[pos.row][pos.col];
    // bonus for remaining reachable treasure on map
    if(cur_card.getTreasure() > 3 &&
       situation.found_treasures_.find(cur_card.getTreasure()) == situation.found_treasures_.end()) {
      score += settings_.reachableTreasureValue;
    }

    // bonus for reachable home, scaled by remaining treasures, since it will gradually become more important
    int remaining = situation.players_[situation_.player_id_-1].remainingTreasures_;
    if(cur_card.getTreasure() == situation.player_id_ -1 &&
        remaining <= settings_.reachableHomeCutoff) {
      score += (settings_.reachableHomeValue/remaining);
    }
  }

  return score;
}

int HeuristicStrategy::evaluate_position_score(const GameSituation& situation, const Position& position) {
  int score = 0;

  auto& cur_card = situation.board_.cards_[position.row][position.col];

  if(cur_card.getTreasure() == situation.treasure_) {
    score += settings_.onTreasureScore;
  } else {
    for(int row = 0; row < 7; ++row) {
      for(int col = 0; col < 7; ++col) {
        if(situation.board_.cards_[row][col].getTreasure() == situation.treasure_) {
          int distance = ::abs(position.row-row) + ::abs(position.col - col);
          score += settings_.distanceBaseValue/(distance*settings_.distanceFactor);
        }
      }
    }
  }

  // a lot of smart stuff can happen here

  return score;
}