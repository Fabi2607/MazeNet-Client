#ifndef ARPCONNECTION_HPP
#define ARPCONNECTION_HPP

#include "ARPTarget.hpp"

class ArpConnection {
  ArpTarget target_one;
  ArpTarget target_two;

public:
  ArpConnection(ArpTarget t1, ArpTarget t2);

  /**
   * Sends faked ARP replys to both targets to relay their traffic over the
   * mac address given by hwAddr. This is essentially a Man-in-the-Middle attack.
   * @hwAddr the mac address of the interface of the 'Man-in-the-Middle'.
   */
  void spoof(uint64_t hwAddr);
};

#endif
