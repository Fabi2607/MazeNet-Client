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
  using namespace mazenet::util::cfg;

  CfgManager& cfgMan = CfgManager::instance();

  if (cfgMan.parseCmdLineOptions(argc, argv) == ExecutionMode::RUN) {
    TcpClient client;
    auto con = client.getConnection();

    client.openConnection(cfgMan.get<std::string>("server.host"), cfgMan.get<std::string>("server.port"));

    MazeCom login_message(MazeComType(MazeComType::LOGIN), 1);

    login_message.LoginMessage(LoginMessageType(cfgMan.get<std::string>("player.name")));

    std::stringstream ss;
    MazeCom_(ss, login_message);

    client.getConnection()->send(ss.str());

    client.getIOService().run();
  }

  return 0;
}
