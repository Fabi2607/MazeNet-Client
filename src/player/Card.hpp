//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_CARD_H
#define MAZENET_CLIENT_CARD_H

#include <iostream>

class Card {
 public:
  inline Card() : openings_(0), treasure_(0), pins_() {

  }

  inline Card(int openings, int treasure) : openings_(openings), treasure_(treasure), pins_() {

  }

  enum Opening {
    UP = 1 << 0,
    RIGHT = 1 << 1,
    DOWN = 1 << 2,
    LEFT = 1 << 3
  };

  inline bool isOpen(Opening direction) const {
    return (bool)(openings_ & direction);
  }

  inline void setOpen(Opening direction) {
    openings_ |= direction;
  }

  inline void setClosed(Opening direction) {
    openings_ &= ~direction;
  }

  inline int getTreasure() const {
    return treasure_;
  }

  inline bool hasPlayer(int player_id) const {
    return (bool)(pins_ & (1 << (player_id - 1)));
  }

  void setPlayer(int player_id) {
    pins_ |= (1 << (player_id-1));
  }

  inline void setTreasure(int treasure) {
    treasure_ = treasure;
  }

  inline void rotateLeft() {
    // UP -> LEFT
    // RIGHT -> UP
    // DOWN -> RiGHT
    // LEFT -> DOWN
    bool up_set = (bool)(openings_ & UP);
    openings_ >>= 1;
    if(up_set) {
      openings_ |= LEFT;
    }
  }

  inline void rotateRight() {
    // LEFT -> UP
    // DOWN -> LEFT
    // RIGHT -> DOWN
    // UP -> RIGHT
    bool left_set = (bool)(openings_ & LEFT);
    openings_ <<= 1;
    openings_ &= 0xF;
    if(left_set) {
      openings_ |= UP;
    }
  }

  friend std::ostream& operator<< (std::ostream& stream, const Card& card) {
    switch(card.openings_) {
      case Card::UP | Card::DOWN: stream << "║"; break;
      case Card::UP | Card::LEFT: stream << "╝"; break;
      case Card::UP | Card::RIGHT: stream << "╚"; break;
      case Card::UP | Card::DOWN | Card::LEFT: stream << "╣"; break;
      case Card::UP | Card::DOWN | Card::RIGHT: stream << "╠"; break;
      case Card::UP | Card::LEFT | Card::RIGHT: stream << "╩"; break;
      case Card::UP | Card::DOWN | Card::LEFT | Card::RIGHT: stream << "╬"; break;
      case Card::DOWN | Card::LEFT: stream << "╗"; break;
      case Card::DOWN | Card::RIGHT: stream << "╔"; break;
      case Card::DOWN | Card::LEFT | Card::RIGHT: stream << "╦"; break;
      case Card::LEFT | Card::RIGHT: stream << "═"; break;
      default: stream << " ";
    }
    return stream;
  }

 private:
  int openings_;
  int treasure_;
  int pins_;
};


#endif //MAZENET_CLIENT_CARD_H
