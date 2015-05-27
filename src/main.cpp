/**
 * @file main.cpp
 * @author Dark Dev
 * @date 27-05-2015
 * @brief
 */

#include <sstream>

#include "network/TcpClient.hpp"
#include "util/cfg/CfgManager.hpp"
#include "messaging/mazeCom.hxx"

int main(int argc, char *argv[]) {
  TcpClient client;
  auto con = client.getConnection();

  client.openConnection("127.0.0.1","5123");

  MazeCom login_message(MazeComType(MazeComType::LOGIN), 1);

  login_message.LoginMessage(LoginMessageType("Klaus"));

  std::stringstream ss;
  MazeCom_(ss,login_message);

  client.getConnection()->send(ss.str());

  client.getIOService().run();

  return 0;
}
