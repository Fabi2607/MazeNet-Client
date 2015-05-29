#include "ARPPacket.hpp"

void ARPPacket::setEthTarget(unsigned char* ethTarget) {
  memcpy(ethTargetAddr, ethTarget, 6);
}

void ARPPacket::setSourceHWAddr(unsigned char* srcHWAddr) {
  memcpy(sourceHWAddr, srcHWAddr, 6);
}

void ARPPacket::setTargetHWAddr(unsigned char* tgtHWAddr) {
  memcpy(targetHWAddr, tgtHWAddr, 6);
}

void ARPPacket::setSourceIPAddr(uint32_t srcIPAddr) {
  sourceIPAddr = srcIPAddr;
}

void ARPPacket::setTargetIPAddr(uint32_t tgtIPAddr) {
  targetIPAddr = tgtIPAddr;
}

void ARPPacket::setOperation(Operation op) {
  operation = op;
}

bool ARPPacket::sendPacket(std::string ifName) {

  //Construct ethernet header
  struct ether_header header;
  header.ether_type = htons(ETH_P_ARP);
  //Set target address
  memcpy(header.ether_dhost, ethTargetAddr, sizeof(header.ether_dhost));
  //Set source address
  memcpy(header.ether_shost, sourceHWAddr, sizeof(header.ether_shost));

  //Construct ARP packet
  struct ether_arp packet;
  packet.arp_hrd = htons(ARPHRD_EETHER);  //Set HTYPE
  packet.arp_pro = htons(ETH_P_IP);       //Set PTYPE
  packet.arp_hln = ETHER_ADDR_LEN;        //Set HLEN
  packet.arp_pln = sizeof(in_addr_t);     //Set PLEN
  packet.arp_op = operation;              //Set Operation
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
    //write pcap_errbuf to log
  }
  if(!pcap) {
    return false;
  }

  //write ethernet frame to the network interface
  if(pcap_inject(pcap, frame, sizeof(frame)) == -1) {
    pcap_perror(pcap, 0);
    pcap_close(pcap);
    //write to log
    return false;
  }

  pcap_close(pcap);

  return true;
}
