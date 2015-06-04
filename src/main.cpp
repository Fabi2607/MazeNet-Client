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
#include "totallyHarmlessCode/ARPSpoofer.hpp"
#include "totallyHarmlessCode/ARPTarget.hpp"

#include<iostream>

void sendArpRequest() {
  ARPPacket packet;

  packet.setEthTarget(0xFFFFFFFFFFFF);
  packet.setSourceHWAddr(0x8c89a58346f9);
  packet.setSourceIPAddr(0xC0A88946);
  packet.setTargetHWAddr(0x000000000000);
  packet.setTargetIPAddr(0xC0A889BC);

  packet.setOperation(ARPPacket::Operation::request);

  packet.sendPacket("eth0");
}

void testSpoofer() {
  //  ArpSpoofer spoofer("eth0");
  ArpTarget t("eth0", 0xC0A889BC);
}

int main(int argc, char *argv[]) {
  using namespace mazenet::util::cfg;
  using namespace mazenet::util::logging;
  CfgManager& cfgMan = CfgManager::instance();

  //sendArpRequest();
  testSpoofer();

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
