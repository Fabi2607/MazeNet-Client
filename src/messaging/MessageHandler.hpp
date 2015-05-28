/**
 * @file MessageHandler.hpp
 * @author Dark Dev
 * @date 27-05-2015
 * @brief
 */

#ifndef _MESSAGEHANDLER_HPP_
#define _MESSAGEHANDLER_HPP_

#include <string>
#include <player/IPlayerStrategy.hpp>

#include "../messaging/mazeCom.hxx"
#include "../player/GameSituation.hpp"
#include "../util/logging/Log.hpp"
#include "MessageDispatcher.hpp"

class MessageHandler {
 public:
  MessageHandler(std::shared_ptr<IPlayerStrategy> strategy, MessageDispatcher& dispatcher);

  void handle_incoming_message(const std::string& message);

 private:
  void handle_login_reply(const LoginReplyMessageType& reply);
  void handle_await_move(const AwaitMoveMessageType& await_move);
  void handle_accept_message(const AcceptMessageType& accept_message);
  void handle_win_message(const WinMessageType& win_message);
  void handle_disconnect_message(const DisconnectMessageType& disconnect_message);

  void update_model(const AwaitMoveMessageType& message);
  void update_board(const boardType& board);

  std::shared_ptr<IPlayerStrategy> strategy_;
  mazenet::util::logging::Log logger_;

  MessageDispatcher& dispatcher_;
};

#endif /* _MESSAGEHANDLER_HPP_ */
