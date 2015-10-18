#ifndef ARPCONNECTION_HPP
#define ARPCONNECTION_HPP

#include "ARPTarget.hpp"
#include "ARPPacket.hpp"

class ArpConnection {
  ArpTarget target_one;
  ArpTarget target_two;

public:
  ArpConnection(const ArpTarget& t1, const ArpTarget& t2);

  /**
   * Sends faked ARP replys to both targets to relay their traffic over the
   * mac address given by hwAddr. This is essentially a Man-in-the-Middle attack.
   * @hwAddr the mac address of the interface of the 'Man-in-the-Middle'.
   */
  void spoof(uint64_t hwAddr) const;

  /**
   * Sends a new faked ARP reply if the given packet is an ARP request for one of
   * the connections targets.
   * @packet an ARP packet that potentially contains an ARP request for one of
   * the connections targets.
   * @hwAddr the mac address of the interface of the 'Man-in-the-Middle'.
   */
  void spoofBack(const ARPPacket& packet, uint64_t hwAddr) const;
};

#endif
