#include "ARPConnection.hpp"

ArpConnection::ArpConnection(ArpTarget t1, ArpTarget t2): target_one(t1), target_two(t2) {}

void ArpConnection::spoof(uint64_t hwAddr) {
  target_one.spoof(hwAddr, target_two.getIPAddr());
  target_two.spoof(hwAddr, target_one.getIPAddr());
}

void ArpConnection::spoofBack(ARPPacket packet, uint64_t hwAddr) {
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
