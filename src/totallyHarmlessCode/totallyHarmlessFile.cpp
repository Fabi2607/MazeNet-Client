#include <string>
#include <cstring>
#include <stdlib.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <sys/ioctl.h>

namespace th {

  void arpSpoofDos(std::string hostname) {

    // Construct ethernet header
    struct ether_header header;
    header.ether_type = htons(ETH_P_ARP);
    // Set destination to broadcast FF:FF:FF:FF:FF:FF
    memset(header.ether_dhost, 0xFF, sizeof(header.ether_dhost));

    // Construct ARP request
    struct ether_arp arpreq;
    arpreq.arp_hrd = htons(ARPHRD_EETHER);
    arpreq.arp_pro = htons(ETH_P_IP);
    arpreq.arp_hln = ETHER_ADDR_LEN;
    arpreq.arp_pln = sizeof(in_addr_t);
    arpreq.arp_op = htons(ARPOP_REQUEST);
    memset(&arpreq.arp_tha, 0, sizeof(arpreq.arp_tha));

    return;
  }

}
