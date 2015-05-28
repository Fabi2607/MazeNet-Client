//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_BOARD_H
#define MAZENET_CLIENT_BOARD_H


#include "Card.hpp"
#include "Position.hpp"

#include <iostream>

class Board {
 public:
  Card insert_card(Card card,Position new_pos);

  Card cards_[7][7];

  friend std::ostream& operator<< (std::ostream& stream, const Board& board) {
    for(int x=0; x<7;++x) {
      for(int y=0; y<7;++y) {
        stream << board.cards_[x][y];
      }
      stream << std::endl;
    }
    return stream;
  }
};



#endif //MAZENET_CLIENT_BOARD_H
