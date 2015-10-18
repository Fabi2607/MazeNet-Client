#include "ARPPacket.hpp"
#include "structures.h"
#include <iostream>
#include <algorithm>

ARPPacket::ARPPacket(): ethTargetAddr(),
			sourceHWAddr(), targetHWAddr(),
			sourceIPAddr(0), targetIPAddr(0),
                        operation(ARPPacket::Operation::request){}

ARPPacket::ARPPacket(const u_char* packet): ethTargetAddr(),
					    sourceHWAddr(), targetHWAddr(),
					    sourceIPAddr(0), targetIPAddr(0),
                                            operation(ARPPacket::Operation::request){
  struct etherhdr* eth_header;
  struct ether_arp* arp_packet;

  eth_header = (struct etherhdr*) packet;
  setEthTarget(hwFromArray(eth_header->ether_dhost));

  arp_packet = (struct ether_arp*) (packet + sizeof(etherhdr));
  setSourceHWAddr(hwFromArray(arp_packet->arp_sha));
  setTargetHWAddr(hwFromArray(arp_packet->arp_tha));
  sourceIPAddr = ipFromArray(arp_packet->arp_spa);
  targetIPAddr = ipFromArray(arp_packet->arp_tpa);

  operation = ntohs(arp_packet->ea_hdr.ar_op) == 1?
    ARPPacket::Operation::request: ARPPacket::Operation::reply;
}



/**
 * Converts a MAC Address, stored in a 6 Byte unsigned char array, into a uint64_t.
 */
uint64_t ARPPacket::hwFromArray(const unsigned char* arr) {
  uint64_t value = 0;
  for(int i = 0; i < 6; ++i) {
    uint64_t tmp = arr[i];
    tmp &= 0xFF;
    value |= tmp << 8 * (6 - 1 - i);
  }
  return value;
}

uint32_t ARPPacket::ipFromArray(const unsigned char* arr) {
  uint32_t value = 0;
  for(int i = 0; i < 4; ++i) {
    uint32_t tmp = arr[i];
    tmp &= 0xFF;
    value |= tmp << 8 * (4 - 1 - i);
  }
  return value;
}

void ARPPacket::setEthTarget(uint64_t ethTarget) {
  unsigned char* tmpAddr = (unsigned char*) &ethTarget;
  memcpy(ethTargetAddr, tmpAddr, 6);
  std::reverse(&ethTargetAddr[0], &ethTargetAddr[6]);
}

uint64_t ARPPacket::getEthTarget() const {
  return hwFromArray(ethTargetAddr);
}

void ARPPacket::setSourceHWAddr(uint64_t srcHWAddr) {
  unsigned char* tmpAddr = (unsigned char*) &srcHWAddr;
  memcpy(sourceHWAddr, tmpAddr, 6);
  std::reverse(&sourceHWAddr[0], &sourceHWAddr[6]);
}

uint64_t ARPPacket::getSourceHWAddr() const {
  return hwFromArray(sourceHWAddr);
}

void ARPPacket::setTargetHWAddr(uint64_t tgtHWAddr) {
  unsigned char* tmpAddr = (unsigned char*) &tgtHWAddr;
  memcpy(targetHWAddr, tmpAddr, 6);
  std::reverse(&targetHWAddr[0], &targetHWAddr[6]);
}

uint64_t ARPPacket::getTargetHWAddr() const {
  return hwFromArray(targetHWAddr);
}

void ARPPacket::setSourceIPAddr(uint32_t srcIPAddr) {
  sourceIPAddr = htonl(srcIPAddr);
}

uint32_t ARPPacket::getSourceIPAddr() const {
  return sourceIPAddr;
}

void ARPPacket::setTargetIPAddr(uint32_t tgtIPAddr) {
  targetIPAddr = htonl(tgtIPAddr);
}

uint32_t ARPPacket::getTargetIPAddr() const {
  return targetIPAddr;
}

void ARPPacket::setOperation(Operation op) {
  operation = op;
}

ARPPacket::Operation ARPPacket::getOperation() const {
  return operation;
}

bool ARPPacket::sendPacket(const std::string& ifName) {

  //Construct ethernet header
  struct ether_header header;
  header.ether_type = htons(ETH_P_ARP);
  //Set target address
  memcpy(header.ether_dhost, ethTargetAddr, sizeof(header.ether_dhost));
  //Set source address
  memcpy(header.ether_shost, sourceHWAddr, sizeof(header.ether_shost));

  //Construct ARP packet
  struct ether_arp packet;
  packet.arp_hrd = htons(ARPHRD_ETHER);   //Set HTYPE
  packet.arp_pro = htons(ETH_P_IP);       //Set PTYPE
  packet.arp_hln = ETHER_ADDR_LEN;        //Set HLEN
  packet.arp_pln = sizeof(in_addr_t);     //Set PLEN
  packet.arp_op = htons(operation);       //Set Operation
  //Set target hardware address
  memcpy(&packet.arp_tha, targetHWAddr, sizeof(packet.arp_tha));
  //Set source hardware address
  memcpy(&packet.arp_sha, sourceHWAddr, sizeof(packet.arp_sha));
  //Set target protocol address
  memcpy(&packet.arp_tpa, &targetIPAddr, sizeof(packet.arp_tpa));
  //Set source protocol address
  memcpy(&packet.arp_spa, &sourceIPAddr, sizeof(packet.arp_spa));

  //Combine ethernet header and APR packet
  unsigned char frame[sizeof(struct ether_header) + sizeof(ether_arp)];
  memcpy(frame, &header, sizeof(struct ether_header));
  memcpy(frame + sizeof(struct ether_header), &packet, sizeof(struct ether_arp));

  //Open PCAP packet capture descriptor
  char pcap_errbuf[PCAP_ERRBUF_SIZE];
  pcap_errbuf[0] = '\0';
  pcap_t* pcap = pcap_open_live(ifName.c_str(), 96, 0, 0, pcap_errbuf);
  if(pcap_errbuf[0] != '\0') {
    std::cerr << "pcaperr: " << std::endl << "  " << pcap_errbuf << std::endl;
  }
  if(!pcap) {
    std::cerr << "pcap capture descriptor could not be created!" << std::endl;
    return false;
  }

  //write ethernet frame to the network interface
  if(pcap_inject(pcap, frame, sizeof(frame)) == -1) {
    pcap_perror(pcap, 0);
    pcap_close(pcap);
    std::cerr << "error writing eth frame!" << std::endl;
    return false;
  }

  pcap_close(pcap);

  return true;
}
