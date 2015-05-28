/**
 * @file MessageHandler.cpp
 * @author Fabian Kantereit
 * @date 27-05-2015
 * @brief
 */

#include "MessageHandler.hpp"
#include "../player/Card.hpp"

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

  // if we receive a message we will update our board
  // and start calculationg the next move
  update_model(await_move);
}

void MessageHandler::handle_accept_message(const AcceptMessageType& accept_message) {
  logger_.log() << "Recceived Accept " << accept_message << logger_.end();
}

void MessageHandler::handle_win_message(const WinMessageType& win_message) {
  update_board(win_message.board());
  if(logic_.getPlayer_id() == win_message.winner().id()) {
    logger_.logSeverity(mazenet::util::logging::SeverityLevel::critical)
        << "WIN!" << logger_.end();
  } else {
    logger_.logSeverity(mazenet::util::logging::SeverityLevel::critical)
        << "LOSE! (" << win_message.winner().id() << " won)" << logger_.end();
  }

  // we should do this more gracefully
  exit(0);
}

void MessageHandler::handle_disconnect_message(const DisconnectMessageType& disconnect_message) {
  logger_.log() << "Received DisconnectMessage" << disconnect_message << logger_.end();

  // we should do this more gracefully
  exit(1);
}

void MessageHandler::update_model(const AwaitMoveMessageType& message) {

  auto board = message.board();

  int player_count = 0;
  for(auto treasureToGo: message.treasuresToGo()) {
    logic_.players_[treasureToGo.player()-1].remainingTreasures_ = treasureToGo.treasures();
    player_count++;
  }

  logic_.found_treasures_.clear();
  for(auto treasure: message.foundTreasures()) {
    logic_.found_treasures_.insert(treasure);
  }

  logic_.player_count_ = player_count;
  logic_.treasure_ = message.treasure();

  auto shiftCard = board.shiftCard();
  int openings = 0;
  if(shiftCard.openings().bottom()) {
    openings |= Card::DOWN;
  }
  if(shiftCard.openings().top()) {
    openings |= Card::UP;
  }
  if(shiftCard.openings().left()) {
    openings |= Card::LEFT;
  }
  if(shiftCard.openings().right()) {
    openings |= Card::RIGHT;
  }
  logic_.shiftCard_ = Card(openings, shiftCard.treasure().present() ? shiftCard.treasure().get() : -1);

  if(board.forbidden().present()) {
    logic_.forbidden_col_ = board.forbidden()->col();
    logic_.forbidden_row_ = board.forbidden()->row();
  } else {
    logic_.forbidden_col_ = -1;
    logic_.forbidden_row_ = -1;
  }

  update_board(board);
}

void MessageHandler::update_board(const boardType& board) {
  int cur_row = 0;
  int cur_col = 0;
  int openings = 0;

  for(auto row: board.row()) {
    cur_col=0;
    for(auto col: row.col()) {
      openings = 0;
      if(col.openings().bottom()) {
        openings |= Card::DOWN;
      }
      if(col.openings().top()) {
        openings |= Card::UP;
      }
      if(col.openings().left()) {
        openings |= Card::LEFT;
      }
      if(col.openings().right()) {
        openings |= Card::RIGHT;
      }
      int treasure = 0;
      if(col.treasure().present()) {
        treasure = col.treasure().get();
        if(treasure < 4){
          logic_.players_[treasure].home_row_ = cur_row;
          logic_.players_[treasure].home_col_ = cur_col;
        }
        logger_.log() << "T" << treasure << "(" << cur_row << "|" << cur_col << ")" << logger_.end();
      } else {
        treasure = -1;
      }
      logic_.board_.cards_[cur_row][cur_col] = Card(openings, treasure);
      ++cur_col;
    }
    ++cur_row;
  }
  logger_.log() << "Updated Board: \n" << logic_.board_ << "" << logger_.end();
}