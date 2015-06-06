#include "ARPConnection.hpp"

ArpConnection::ArpConnection(ArpTarget t1, ArpTarget t2): target_one(t1), target_two(t2) {}

void ArpConnection::spoof(uint64_t hwAddr) {
  target_one.spoof(hwAddr, target_two.getIPAddr());
  target_two.spoof(hwAddr, target_one.getIPAddr());
}
