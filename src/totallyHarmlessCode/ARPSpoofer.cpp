#include "ARPSpoofer.hpp"
#include "ARPPacket.hpp"
#include "structures.h"

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>

#include <stdio.h>

ArpSpoofer::ArpSpoofer(std::string pInterfaceName): connections(), interfaceName(pInterfaceName),
						    macAddr(getMacForInterface(interfaceName)),
						    ipAddr(getIpForInterface(interfaceName)),
						    spoofing(false) {}

bool ArpSpoofer::addConnection(const ArpConnection& connection) {
  if(spoofing) return false;

  connections.push_back(connection);
  return true;
}

uint64_t ArpSpoofer::getMacForInterface(std::string ifName) {
  int rsocket;
  struct ifreq buffer;
  rsocket = socket(PF_INET, SOCK_DGRAM, 0);

  memset(&buffer, 0x00, sizeof(buffer));
  strcpy(buffer.ifr_name, ifName.c_str());
  ioctl(rsocket, SIOCGIFHWADDR, &buffer);
  close(rsocket);

  uint64_t value = 0;
  for(int i = 0; i < 6; ++i) {
    uint64_t tmp = buffer.ifr_hwaddr.sa_data[i];
    tmp &= 0xFF;
    value |= (tmp  << (8 * (6 - i - 1)));
  }
  return value;
}

uint32_t ArpSpoofer::getIpForInterface(std::string ifName) {
  int rsocket;
  struct ifreq buffer;

  rsocket = socket(AF_INET, SOCK_DGRAM, 0);
  buffer.ifr_addr.sa_family = AF_INET;
  strcpy(buffer.ifr_name, ifName.c_str());
  ioctl(rsocket, SIOCGIFADDR, &buffer);
  close(rsocket);

  char* chr = inet_ntoa(((struct sockaddr_in *)&buffer.ifr_addr)->sin_addr);
  uint32_t value = 0;
  for(int i = 0; i < 6; ++i) {
    uint32_t tmp = buffer.ifr_addr.sa_data[i];
    tmp &= 0xFF;
    value |= (tmp << (8 * (6 - i - 1)));
  }

  return value;
}
