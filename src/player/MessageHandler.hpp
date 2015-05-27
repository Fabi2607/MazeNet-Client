/**
 * @file MessageHandler.hpp
 * @author Dark Dev
 * @date 27-05-2015
 * @brief
 */

#ifndef _MESSAGEHANDLER_HPP_
#define _MESSAGEHANDLER_HPP_

#include <string>

class MessageHandler {
 public:
  void handle_incoming_message(const std::string& message);

};

#endif /* _MESSAGEHANDLER_HPP_ */
