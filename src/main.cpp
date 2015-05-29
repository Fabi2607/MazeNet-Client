/**
 * @file main.cpp
 * @author Dark Dev
 * @date 27-05-2015
 * @brief
 */

#include <sstream>
#include <messaging/MessageDispatcher.hpp>
#include <player/HeuristicStrategy.hpp>

#include "network/TcpClient.hpp"
#include "util/cfg/CfgManager.hpp"
#include "util/logging/Log.hpp"
#include "messaging/mazeCom.hxx"
#include "messaging/MessageHandler.hpp"

#include "totallyHarmlessCode/ARPPacket.hpp"

#include<iostream>

void sendArpRequest() {
  ARPPacket packet;

  uint64_t ethTgtAddr = 0xFFFFFFFFFFFF;
  packet.setEthTarget((unsigned char*)&ethTgtAddr);
  uint64_t srcHWAddr = 0xe018770a4faf;
  packet.setSourceHWAddr((unsigned char*)&srcHWAddr);
  packet.setSourceIPAddr(0xC0A88946);
  uint64_t tgtHWAddr = 0x000000000000;
  packet.setTargetHWAddr((unsigned char*)&tgtHWAddr);
  packet.setTargetIPAddr(0xC0A889BC);

  packet.setOperation(ARPPacket::Operation::request);

  packet.sendPacket("eth1");
}

int main(int argc, char *argv[]) {
  using namespace mazenet::util::cfg;
  using namespace mazenet::util::logging;
  CfgManager& cfgMan = CfgManager::instance();

  sendArpRequest();

  /*
  // keep as first line
  if (cfgMan.parseCmdLineOptions(argc, argv) == ExecutionMode::RUN) {
    Log logger("main");

    TcpClient client;
    auto con = client.getConnection();
    auto host = cfgMan.get<std::string>("server.host");
    auto port = cfgMan.get<std::string>("server.port");

    logger.log() << "Connecting to: " << host << ":" << port << logger.end();
    client.openConnection(host, port);

    MessageDispatcher dispatcher(client.getConnection());
    MessageHandler handler(std::make_shared<HeuristicStrategy>(), dispatcher);

    client.getConnection()->setReadHandler([&handler](const std::string& msg) {
        handler.handle_incoming_message(msg);
      });

    dispatcher.sendLoginMessage("DarkDev");

    client.getIOService().run();
  }
  */
  return 0;
}
