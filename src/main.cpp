/**
 * @file main.cpp
 * @author Dark Dev
 * @date 27-05-2015
 * @brief
 */

#include <sstream>

#include "network/TcpClient.hpp"
#include "util/cfg/CfgManager.hpp"
#include "util/logging/Log.hpp"
#include "messaging/mazeCom.hxx"
#include "player/MessageHandler.hpp"

int main(int argc, char *argv[]) {
  using namespace mazenet::util::cfg;
  using namespace mazenet::util::logging;
  CfgManager& cfgMan = CfgManager::instance();

  // keep as first line
  if (cfgMan.parseCmdLineOptions(argc, argv) == ExecutionMode::RUN) {
    Log logger("main");

    TcpClient client;
    auto con = client.getConnection();
    auto host = cfgMan.get<std::string>("server.host");
    auto port = cfgMan.get<std::string>("server.port");

    logger.log() << "Connecting to: " << host << ":" << port << logger.end();
    client.openConnection(host, port);

    GameLogic logic;
    MessageHandler handler(logic);
    client.getConnection()->setReadHandler([&handler](const std::string& msg) {
        handler.handle_incoming_message(msg);
      });


    MazeCom login_message(MazeComType(MazeComType::LOGIN), 1);
    login_message.LoginMessage(LoginMessageType(cfgMan.get<std::string>("player.name")));

    std::stringstream ss;
    MazeCom_(ss, login_message);

    client.getConnection()->send(ss.str());
    client.getIOService().run();
  }

  return 0;
}
