#ifndef ARPCONNECTION_HPP
#define ARPCONNECTION_HPP

#include "ARPTarget.hpp"
#include "ARPPacket.hpp"
#include "IPPacket.hpp"


class ArpConnection {
  ArpTarget target_one;
  ArpTarget target_two;

public:
  ArpConnection(ArpTarget t1, ArpTarget t2);

  /**
   * Sends faked ARP replies to both targets to relay their traffic over the
   * mac address given by hwAddr. This is essentially a Man-in-the-Middle attack.
   * @hwAddr the mac address of the interface of the 'Man-in-the-Middle'.
   */
  void spoof(uint64_t hwAddr);

  /**
   * Sends a new faked ARP reply if the given packet is an ARP request for one of
   * the connections targets.
   * @packet an ARP packet that potentially contains an ARP request for one of
   * the connections targets.
   * @hwAddr the mac address of the interface of the 'Man-in-the-Middle'.
   */
  void spoofBack(ARPPacket packet, uint64_t hwAddr);

  void process(IPPacket packet);
};

#endif
