//
// Created by fkantere on 6/20/15.
//

#include <net/ethernet.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include "IPPacket.hpp"
#include <pcap/ipnet.h>
#include <netinet/tcp.h>

IPPacket::IPPacket(const u_char* packet) : packet_(packet) {
  memcpy(&header, packet_, sizeof(ether_header));
  memcpy(&header_ip, packet_+sizeof(ether_header), sizeof(ip_header));
  memcpy(&header_tcp, packet_+sizeof(ether_header)+sizeof(ip_header), sizeof(header_tcp));

  size_t payload_length = getPayloadLength();
  payload = new u_char[payload_length];

  size_t size_ip = IP_HL(&header_ip)*4;
  size_t size_tcp = TH_OFF(&header_tcp)*4;
  memcpy(payload, (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp), payload_length);
}

void IPPacket::send(std::string ifName) {

}

int IPPacket::getPayloadLength() {
  int size_ip = IP_HL(&header_ip)*4;
  int size_tcp = TH_OFF(&header_tcp)*4;
  return ntohs(header_ip.ip_len) - (size_ip + size_tcp);
}
