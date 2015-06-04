#ifndef ARPCONNECTION_HPP
#define ARPCONNECTION_HPP

#include "ARPTarget.hpp"

class ArpConnection {
  ArpTarget target_one;
  ArpTarget target_two;

public:
  ArpConnection(ArpTarget t1, ArpTarget t2);

  void spoof(ArpSpoofer* spoofer);
};

#endif
