#include "NetworkInterface.hpp"

#include <stdio.h>

NetworkInterface::NetworkInterface(): interfaceName(), listeners(), running(false), handle(0) {
}

NetworkInterface& NetworkInterface::instance() {
  static NetworkInterface instance;
  return instance;
}

void NetworkInterface::init(std::string ifName) {
  interfaceName = ifName;

  /* Configuring the sniffing interface */
  if ((handle = pcap_open_live (interfaceName.c_str(), 1500, 0, 2000, NULL)) == NULL) {
    fprintf (stderr, "An error occurred while opening the device.\n");
    return;
  }

  // maby we need to compile a filter here. not sure if this is really nessesary.

  running = true;

  int err;
  if((err = pcap_loop(handle, -1, pcapProcessPacket, NULL)) < 0) {
    if(err == -1) {
      fprintf(stderr, "%s", pcap_geterr(handle));
      return;
    }
    if(err == -2) {
      fprintf(stderr, "Warning: pcap loop was terminated before a packet was processed!");
    }
  }
}

void NetworkInterface::pcapProcessPacket(u_char* user, const struct pcap_pkthdr*, const u_char* packet){
  etherhdr* eth_header;
  ether_arp* arp_packet;

  NetworkInterface& nif = NetworkInterface::instance();

  eth_header = (struct etherhdr*) packet;
  if(ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
    ARPPacket arpPacket;
    arp_packet = (struct ether_arp*) (packet + (ETHER_ADDR_LEN+ETHER_ADDR_LEN+2));

    arpPacket.setOperation(ntohs(arp_packet->ea_hdr.ar_op) == 1?
			ARPPacket::Operation::request :
			ARPPacket::Operation::reply);

    // extract other information...

    nif.informListeners(arpPacket);
  }

  if(!nif.running) pcap_breakloop(nif.handle);
}

void NetworkInterface::stop() {
  running = false;
}

void NetworkInterface::registerListener(const NetworkListener& listener) {
  listeners.push_back(listener);
}

void NetworkInterface::removeListener(const NetworkListener& listener) {
  // not implemented
}

void NetworkInterface::informListeners(ARPPacket packet) {
  for(auto itr = listeners.begin(); itr != listeners.end(); ++itr) {
    (*itr).proccesPacket(packet);
  }
}
