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

#include "w3p0nz/arpdos/ARPPacket.hpp"
#include "w3p0nz/arpdos/ARPSpoofer.hpp"
#include "w3p0nz/arpdos/ARPTarget.hpp"
#include "w3p0nz/arpdos/ARPConnection.hpp"
#include "w3p0nz/arpdos/ARPScanner.hpp"

#include <vector>
#include <iostream>

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
  ArpTarget rpi("eth0", 0xC0A889BC);
  ArpTarget nb("eth0", 0xC0A8899B);

  ArpConnection con(rpi, nb);
  con.spoof(0x8c89a58346f9);
}

void testScanner() {
  std::vector<ArpTarget> targets = ArpScanner::arpScan("eth0");
  std::cout << "Found " << targets.size() << " hosts." << std::endl << std::endl;

  for(auto itr = targets.begin(); itr != targets.end(); ++itr) {
    std::cout << std::hex << (*itr).getIPAddr() << std::endl;
  }
}

int main(int argc, char *argv[]) {
  using namespace mazenet::util::cfg;
  using namespace mazenet::util::logging;
  CfgManager& cfgMan = CfgManager::instance();

  //sendArpRequest();
  //testSpoofer();
  testScanner();

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
