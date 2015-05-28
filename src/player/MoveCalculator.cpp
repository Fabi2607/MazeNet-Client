//
// Created by fkantere on 5/28/15.
//

#include "MoveCalculator.hpp"

std::vector<Move> MoveCalculator::get_possible_moves(GameSituation& situation) {
  std::vector<Move> moves;
  int insert_col = 0;
  int insert_row = 1;
  for(insert_row=1; insert_row<7;insert_row+=2) {
    if(insert_col!=situation.forbidden_col_ || insert_row!=situation.forbidden_row_) {
      Card c = situation.shiftCard_;
      for (int i = 0; i < 4; ++i) {
        Move m;
        m.shift_card = c;
        m.shift_pos = {insert_row, insert_col};
        moves.emplace_back(m);
        c.rotateLeft();
      }
    }
  }

  insert_col = 7;
  for(insert_row=1; insert_row<7;insert_row+=2) {
    if(insert_col!=situation.forbidden_col_ || insert_row!=situation.forbidden_row_) {
      Card c = situation.shiftCard_;
      for (int i = 0; i < 4; ++i) {
        Move m;
        m.shift_card = c;
        m.shift_pos = {insert_row, insert_col};
        moves.emplace_back(m);
        c.rotateLeft();
      }
    }
  }

  insert_row = 0;
  for(insert_col=1; insert_col<7;insert_col+=2) {
    if(insert_col!=situation.forbidden_col_ || insert_row!=situation.forbidden_row_) {
      Card c = situation.shiftCard_;
      for (int i = 0; i < 4; ++i) {
        Move m;
        m.shift_card = c;
        m.shift_pos = {insert_row, insert_col};
        moves.emplace_back(m);
        c.rotateLeft();
      }
    }
  }

  insert_row = 7;
  for(insert_col=1; insert_col<7;insert_col+=2) {
    if(insert_col!=situation.forbidden_col_ || insert_row!=situation.forbidden_row_) {
      Card c = situation.shiftCard_;
      for (int i = 0; i < 4; ++i) {
        Move m;
        m.shift_card = c;
        m.shift_pos = {insert_row, insert_col};
        moves.emplace_back(m);
        c.rotateLeft();
      }
    }
  }

  return moves;
}
