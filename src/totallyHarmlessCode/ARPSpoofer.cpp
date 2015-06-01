#include "ARPSpoofer.hpp"
#include "ARPPacket.hpp"

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>

#include <stdio.h>

ArpTarget::ArpTarget(std::string ifName, uint32_t pTargetIPAddr):
    interfaceName(ifName),
    handle(pcap_open_live (interfaceName.c_str(), 1500, 0, 2000, NULL)),
    targetIPAddr(pTargetIPAddr),
    targetMACAddr(0) {
  getMacAddr();
}

uint32_t ArpTarget::getIPAddr() const { return targetIPAddr; }

uint64_t ArpTarget::getMacAddr() const { return targetMACAddr; }

void ArpTarget::getMacAddr() {
  ARPPacket arpreq;

  arpreq.setEthTarget(0xFFFFFFFFFFFF);                 //Set to broadcast address

  arpreq.setOperation(ARPPacket::Operation::request);  //OP:Request
  //MAC address of device used
  arpreq.setSourceHWAddr(ArpSpoofer::getMacForInterface(interfaceName));
  //IP  address of device used
  arpreq.setSourceIPAddr(ArpSpoofer::getIpForInterface(interfaceName));
  arpreq.setTargetHWAddr(0xFFFFFFFFFFFF);              //Set to broadcast
  arpreq.setTargetIPAddr(targetIPAddr);          //IP address of the target

  //send the ARP request
  arpreq.sendPacket(interfaceName);

  int s;
  if((s = pcap_loop(handle, -1, pcapProcessGetMac, NULL)) < 0) {
    if(s == -1) {
      fprintf(stderr, "%s", pcap_geterr(handle));
      return;
    } else {
      fprintf(stderr, "pcap loop was stopped before a package got processed!");
      return;
    }
  }

  //Got the mac address, don't need this anymore.
  pcap_close(handle);
}

void ArpTarget::pcapProcessGetMac(u_char* user, const struct pcap_pkthdr*, const u_char* packet) {
  struct ethhdr* eth_header;
  struct ether_arp* arp_packet;

  eth_header = (struct ethhdr*) packet;

  if(ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
    arp_packet = (struct ether_arp*) (packet + (ETHER_ADDR_LEN + ETHER_ADDR_LEN + 2));

    //If package is an ARP reply
    if(ntohs(arp_packet->ea_hdr.ar_op) == 2) {
      printf("got ARP reply from %d", arp_packet->arp_spa);

      pcap_breakloop(handle);
    }
  }
}

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
