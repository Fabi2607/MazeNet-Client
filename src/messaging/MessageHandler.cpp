/**
 * @file MessageHandler.cpp
 * @author Dark Dev
 * @date 27-05-2015
 * @brief
 */

#include "MessageHandler.hpp"
#include "../player/Card.hpp"

#include <sstream>
#include <iostream>

MessageHandler::MessageHandler(std::shared_ptr<IPlayerStrategy> strategy, MessageDispatcher& dispatcher) : strategy_(strategy), logger_("network"), dispatcher_(dispatcher) {

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
  strategy_->situation_.player_id_ = reply.newID();
}

void MessageHandler::handle_await_move(const AwaitMoveMessageType& await_move) {
  logger_.log() << "Received: AwaitMove " << logger_.end();

  // if we receive a message we will update our board
  // and start calculating the next move
  update_model(await_move);
  Move m= strategy_->calculate_next_move();
  dispatcher_.sendMove(strategy_->situation_.player_id_, m);
}

void MessageHandler::handle_accept_message(const AcceptMessageType& accept_message) {
  logger_.log() << "Recceived Accept " << accept_message << logger_.end();

  if(accept_message.accept()) {
    strategy_->move_accepted();
  } else {
    strategy_->move_rejected();
    Move m= strategy_->calculate_next_move();
    dispatcher_.sendMove(strategy_->situation_.player_id_, m);
  }
}

void MessageHandler::handle_win_message(const WinMessageType& win_message) {
  update_board(win_message.board());
  if(strategy_->situation_.player_id_ == win_message.winner().id()) {
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
  for(auto& treasureToGo: message.treasuresToGo()) {
    strategy_->situation_.players_[treasureToGo.player()-1].remainingTreasures_ = treasureToGo.treasures();
    player_count++;
  }

  strategy_->situation_.found_treasures_.clear();
  for(auto& treasure: message.foundTreasures()) {
    strategy_->situation_.found_treasures_.insert(treasure);
  }

  strategy_->situation_.player_count_ = player_count;
  strategy_->situation_.treasure_ = message.treasure();

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

  strategy_->situation_.shiftCard_ = Card(openings, shiftCard.treasure().present() ? shiftCard.treasure().get() : -1);

  for(auto& player_id: shiftCard.pin().playerID()) {
    strategy_->situation_.players_[player_id-1].pos_ = {-1,-1}; // player is not on the map
    strategy_->situation_.shiftCard_.setPlayer(player_id);
  }

  if(board.forbidden().present()) {
    strategy_->situation_.forbidden_col_ = board.forbidden()->col();
    strategy_->situation_.forbidden_row_ = board.forbidden()->row();
  } else {
    strategy_->situation_.forbidden_col_ = -1;
    strategy_->situation_.forbidden_row_ = -1;
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
        if(treasure < 4) {
          strategy_->situation_.players_[treasure].home_ = { cur_row, cur_col };
        }
        logger_.log() << "T" << treasure << "(" << cur_row << "|" << cur_col << ")" << logger_.end();
      } else {
        treasure = -1;
      }

      strategy_->situation_.board_.cards_[cur_row][cur_col] = Card(openings, treasure);

      for(auto player_id: col.pin().playerID()) {
        strategy_->situation_.players_[player_id-1].pos_ = {cur_row, cur_col};
        strategy_->situation_.board_.cards_[cur_row][cur_col].setPlayer(player_id);
      }

      ++cur_col;
    }
    ++cur_row;
  }
  logger_.log() << "Updated Board: \n" << strategy_->situation_.board_ << "" << logger_.end();
}