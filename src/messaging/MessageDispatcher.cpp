//
// Created by fkantere on 5/28/15.
//

#include "MessageDispatcher.hpp"

#include "mazeCom.hxx"

MessageDispatcher::MessageDispatcher(TcpConnection::ConnectionPtr connection) : connection_(connection) {

}

void MessageDispatcher::sendLoginMessage(const std::string& name) {
  MazeCom login_message(MazeComType(MazeComType::LOGIN), 0);
  login_message.LoginMessage(LoginMessageType(name));

  std::stringstream ss;
  MazeCom_(ss, login_message);

  connection_->send(ss.str());
}

void MessageDispatcher::sendMove(int player_id, const Move& move) {
  MazeCom mazecom_message(MazeComType::MOVE, player_id);
  positionType shift_position(move.shift_pos.row, move.shift_pos.col);
  positionType new_pin_position(move.new_pos.row, move.new_pos.col);

  openings open(move.shift_card.isOpen(Card::UP),move.shift_card.isOpen(Card::DOWN),
                move.shift_card.isOpen(Card::LEFT), move.shift_card.isOpen(Card::DOWN));

  pin pins;
  for(int i=1; i < 4; ++i) {
    if(move.shift_card.hasPlayer(i))
      pins.playerID().emplace_back(i);
  }

  cardType shift_card(open, pins);

  if(move.shift_card.getTreasure()!=-1) {
    shift_card.treasure().set((treasureType::value)move.shift_card.getTreasure());
  }

  MoveMessageType move_message(shift_position, new_pin_position, shift_card);
  mazecom_message.MoveMessage(move_message);

  std::stringstream ss;
  MazeCom_(ss,mazecom_message);
  connection_->send(ss.str());
}
