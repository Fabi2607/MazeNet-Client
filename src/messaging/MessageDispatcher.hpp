//
// Created by fkantere on 5/28/15.
//

#ifndef MAZENET_CLIENT_MESSAGEDISPATCHER_H
#define MAZENET_CLIENT_MESSAGEDISPATCHER_H


#include <network/TcpConnection.hpp>

#include "../player/Move.hpp"

class MessageDispatcher {
 public:
  MessageDispatcher(TcpConnection::ConnectionPtr connection);

  void sendLoginMessage(const std::string& name);

  void sendMove(int player_id, const Move& move);

 private:
  TcpConnection::ConnectionPtr connection_;
};

#endif //MAZENET_CLIENT_MESSAGEDISPATCHER_H
