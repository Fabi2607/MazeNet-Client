#include "ARPConnection.hpp"

ArpConnection::ArpConnection(const ArpTarget& t1, const ArpTarget& t2): target_one(t1), target_two(t2) {}

void ArpConnection::spoof(uint64_t hwAddr) const {
  target_one.spoof(hwAddr, target_two.getIPAddr());
  target_two.spoof(hwAddr, target_one.getIPAddr());
}

void ArpConnection::spoofBack(const ARPPacket& packet, uint64_t hwAddr) const {
  // Target one asks for target two's mac address.
  if(packet.getSourceIPAddr() == target_one.getIPAddr() &&
     packet.getTargetIPAddr() == target_two.getIPAddr()) {
    target_one.spoof(hwAddr, target_two.getIPAddr());
  }
  // Target two asks for target one's mac address.
  if(packet.getSourceIPAddr() == target_two.getIPAddr() &&
     packet.getTargetIPAddr() == target_one.getIPAddr()) {
    target_two.spoof(hwAddr, target_one.getIPAddr());
  }
}
