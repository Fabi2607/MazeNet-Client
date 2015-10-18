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
  ArpSpoofer(const std::string& pInterfaceName);

  bool addConnection(const ArpConnection& connection);

  void spoof(uint64_t spoofAddr);
  void setSpoofing(bool pSpoofing);

  static uint32_t getIpForInterface(const std::string& ifName);
  static uint64_t getMacForInterface(const std::string& ifName);

};

#endif
