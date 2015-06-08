#ifndef ARPTARGET_HPP
#define ARPTARGET_HPP

#include <pcap.h>
#include <string>

class ArpTarget {
  std::string interfaceName;
  pcap_t* handle;
  uint32_t targetIPAddr;
  uint64_t targetMACAddr;

public:
  static const int MAXRETRY = 5;

  ArpTarget(std::string ifName, uint32_t pTargetIPAddr);

  uint32_t getIPAddr() const;
  uint64_t getMacAddr() const;

  /**
   * Sends an ARP reply to tell the target, that the host given by ipAddr has the Mac address
   * given by hwAddr.
   * @hwAddr source Mac address of the fake reply.
   * @ipAddr source IP address of the fake reply.
   */
  void spoof(uint64_t hwAddr, uint32_t ipAddr);

private:
  void detMacAddr();
  void waitForARPRepley();
};

#endif
