#ifndef ARPSPOOFER_HPP
#define ARPSPOOFER_HPP

#include <pcap.h>
#include <string>
#include <vector>

class ArpSpoofer;

class ArpTarget {
  std::string interfaceName;
  pcap_t* handle;
  uint32_t targetIPAddr;
  uint64_t targetMACAddr;

public:
  ArpTarget(std::string ifName, uint32_t pTargetIPAddr);

  uint32_t getIPAddr() const;
  uint64_t getMacAddr() const;

private:
  void getMacAddr();
  void pcapProcessGetMac(u_char* user, const struct pcap_pkthdr* header, const u_char* packet);
};

class ArpConnection {
  ArpTarget target_one;
  ArpTarget target_two;

public:
  ArpConnection(ArpTarget t1, ArpTarget t2);

  void spoof(ArpSpoofer* spoofer);
  void spoofBack(ArpSpoofer* spoofer, ArpTarget target);
};

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

private:
  void pcapProccesSpoofBack(u_char* user, const struct pcap_pkthdr* header, const u_char* packet);
};

#endif
