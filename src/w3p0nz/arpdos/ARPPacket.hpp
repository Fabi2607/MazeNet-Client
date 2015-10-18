#ifndef ARPPACKET_HPP
#define ARPPACKET_HPP

#include <string>
#include <cstring>
#include <stdlib.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <sys/ioctl.h>
#include <unistd.h>

class ARPPacket {
public:
  enum Operation {request = 1, reply = 2};
private:

  unsigned char ethTargetAddr[6];

  unsigned char sourceHWAddr[6];
  unsigned char targetHWAddr[6];

  uint32_t sourceIPAddr;
  uint32_t targetIPAddr;

  Operation operation;

public:

  ARPPacket();
  ARPPacket(const u_char*);

  /**
   * Getter and Setter for the packets Ethernet address.
   */
  void setEthTarget(uint64_t ethTarget);
  uint64_t getEthTarget() const;

  /**
   * Getter and Setter for the packets source Mac address.
   */
  void setSourceHWAddr(uint64_t srcHWAddr);
  uint64_t getSourceHWAddr() const;

  /**
   * Getter and Setter for the packets target Mac address.
   */
  void setTargetHWAddr(uint64_t tgtHWAddr);
  uint64_t getTargetHWAddr() const;

  /**
   * Getter and Setter for the packets source IP address.
   */
  void setSourceIPAddr(uint32_t srcIPAddr);
  uint32_t getSourceIPAddr() const;

  /**
   * Getter and Setter the packets target IP address.
   */
  void setTargetIPAddr(uint32_t tgtIPAddr);
  uint32_t getTargetIPAddr() const;

  /**
   * Getter and Setter for the packets OPCode (request/reply)
   */
  void setOperation(Operation op);
  Operation getOperation() const;

  /**
   * Sends the packet through the given network interface
   * @ifName the network interface to send the packet through
   * @return true if the packet was send without any problems, false otherwise.
   */
  bool sendPacket(const std::string& ifName);

  static uint32_t ipFromArray(const unsigned char* arr);
  static uint64_t hwFromArray(const unsigned char* arr);

};



#endif
