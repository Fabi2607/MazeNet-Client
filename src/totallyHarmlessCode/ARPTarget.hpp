#ifndef ARPTARGET_HPP
#define ARPTARGET_HPP

#include <pcap.h>
#include <string>

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
  void waitForARPRepley();
};

#endif
