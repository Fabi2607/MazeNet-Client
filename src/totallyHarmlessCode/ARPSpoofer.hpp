#ifndef ARPSPOOFER_HPP
#define ARPSPOOFER_HPP

#include <pcap.h>
#include <string>
#include <vector>

#include "ARPConnection.hpp"

class ArpSpoofer {

  std::vector<ArpConnection> connections;
  std::string interfaceName;
  uint64_t macAddr;
  uint32_t ipAddr;
  bool spoofing;

public:
  ArpSpoofer(std::string pInterfaceName);

  bool addConnection(const ArpConnection& connection);

  void spoof();

  static uint32_t getIpForInterface(std::string ifName);
  static uint64_t getMacForInterface(std::string ifName);

};

#endif
