//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_MOVECALCULATOR_H
#define MAZENET_CLIENT_MOVECALCULATOR_H


#include <vector>
#include "Move.hpp"
#include "GameSituation.hpp"

class MoveCalculator {
 public:
  static std::vector<Move> get_possible_moves(GameSituation& situation);
  static std::vector<Position> get_possible_positions(GameSituation& situation);
 private:

};


#endif //MAZENET_CLIENT_MOVECALCULATOR_H
