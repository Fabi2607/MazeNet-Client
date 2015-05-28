#ifndef ARPPPACKET_HPP
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

namespace arp{

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

    void setEthTarget(unsigned char* ethTarget);

    void setSourceHWAddr(unsigned char* srcHWAddr);
    void setTargetHWAddr(unsigned char* tgtHWAddr);

    void setSourceIPAddr(uint32_t srcIPAddr);
    void setTargetIPAddr(uint32_t tgtIPAddr);

    void setOperation(Operation op);

    bool sendPacket(std::string ifName);
  };

}


#endif
