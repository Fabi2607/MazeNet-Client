#include "ARPScanner.hpp"
#include "ARPSpoofer.hpp"

std::vector<ArpTarget> ArpScanner::arpScan(std::string ifName) {

  std::vector<ArpTarget> ret;

  uint32_t ipAddr = ArpSpoofer::getIpForInterface(ifName);
  for(uint32_t i = ipAddr & 0xFFFFFF00; i <= (ipAddr & 0xFFFFFF00) + 0xFF; ++i) {
    if(i != ipAddr) {
      ArpTarget target(ifName, i);
      if(target.getMacAddr() != 0) {
	ret.push_back(target);
      }
    }
  }

  return ret;
}
