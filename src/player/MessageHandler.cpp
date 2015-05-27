/**
 * @file MessageHandler.cpp
 * @author Fabian Kantereit
 * @date 27-05-2015
 * @brief
 */

#include "MessageHandler.hpp"
#include "../messaging/mazeCom.hxx"

#include <sstream>
#include <iostream>

void MessageHandler::handle_incoming_message(const std::string& message) {
  std::stringstream ss;
  ss << message;

  try {
    auto maze_com = MazeCom_(ss, xml_schema::flags::dont_validate);
  }
  catch (const xml_schema::exception& e)
  {
    std::cerr << e << std::endl;
  }
}
