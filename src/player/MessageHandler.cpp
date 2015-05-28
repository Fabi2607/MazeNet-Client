/**
 * @file MessageHandler.cpp
 * @author Fabian Kantereit
 * @date 27-05-2015
 * @brief
 */

#include "MessageHandler.hpp"

#include <sstream>
#include <iostream>

MessageHandler::MessageHandler(GameLogic& logic) : logic_(logic), logger_("network") {

}

void MessageHandler::handle_incoming_message(const std::string& message) {
  std::stringstream ss;
  ss << message;

  using SeverityLevel = mazenet::util::logging::SeverityLevel;

  logger_.logSeverity(SeverityLevel::trace)
      << message << logger_.end();

  try {
    auto maze_com = MazeCom_(ss, xml_schema::flags::dont_validate);

    switch(maze_com->mcType()) {
      case MazeComType::LOGIN:
        logger_.logSeverity(SeverityLevel::error) << "Received unexpected LoginMessage" << *maze_com << logger_.end();
        break;
      case MazeComType::LOGINREPLY:
        if(maze_com->LoginReplyMessage()) {
          handle_login_reply(maze_com->LoginReplyMessage().get());
        } else {
          logger_.logSeverity(SeverityLevel::error) << "Expected LoginReplyMessage not found" << logger_.end();
        }
        break;
      case MazeComType::AWAITMOVE:
        if(maze_com->AwaitMoveMessage()) {
          handle_await_move(maze_com->AwaitMoveMessage().get());
        } else {
          logger_.logSeverity(SeverityLevel::error) << "Expected AwaitMoveMessage not found" << logger_.end();
        }
        break;
      case MazeComType::MOVE:
        logger_.logSeverity(SeverityLevel::error) << "Received unexpected MoveMessage" << logger_.end();
        break;
      case MazeComType::ACCEPT:
        if(maze_com->AcceptMessage()) {
          handle_accept_message(maze_com->AcceptMessage().get());
        } else {
          logger_.logSeverity(SeverityLevel::error) << "Expected AcceptMessage not found" << logger_.end();
        }
        break;
      case MazeComType::WIN:
        if(maze_com->WinMessage()) {
          handle_win_message(maze_com->WinMessage().get());
        } else {
          logger_.logSeverity(SeverityLevel::error) << "Expected WinMessage not found" << logger_.end();
        }
        break;
      case MazeComType::DISCONNECT:
        if(maze_com->DisconnectMessage()) {
          handle_disconnect_message(maze_com->DisconnectMessage().get());
        } else {
          logger_.logSeverity(SeverityLevel::error) << "Expected DisconectMessage not found" << logger_.end();
        }
        break;
    }
  }
  catch (const xml_schema::exception& e) {
    logger_.logSeverity(SeverityLevel::error) << e << logger_.end();
  }
}

void MessageHandler::handle_login_reply(const LoginReplyMessageType& reply) {
  logger_.log() << "Received: LoginReply " << reply << logger_.end();
  logic_.setPlayer_id(reply.newID());
}

void MessageHandler::handle_await_move(const AwaitMoveMessageType& await_move) {
  logger_.log() << "Received: AwaitMove " << logger_.end();
}

void MessageHandler::handle_accept_message(const AcceptMessageType& accept_message) {
  logger_.log() << "Recceived Accept " << accept_message << logger_.end();
}

void MessageHandler::handle_win_message(const WinMessageType& win_message) {
  logger_.log() << "Received WinMessage" << win_message << logger_.end();
}

void MessageHandler::handle_disconnect_message(const DisconnectMessageType& disconnect_message) {
  logger_.log() << "Received DisconnectMessage" << disconnect_message << logger_.end();
}
