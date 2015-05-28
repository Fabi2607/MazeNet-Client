#include <string>
#include <cstring>
#include <stdlib.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

namespace th {

  /**
   * ATM this does not perform a Dos via ARP but only broadcasts an ARP request to the target.
   */
  void arpSpoofDos(std::string ifName, std::string hostname) {

    // Construct ethernet header
    struct ether_header header;
    header.ether_type = htons(ETH_P_ARP);
    // Set destination to broadcast FF:FF:FF:FF:FF:FF
    memset(header.ether_dhost, 0xFF, sizeof(header.ether_dhost));

    // Construct ARP request
    struct ether_arp arpreq;
    arpreq.arp_hrd = htons(ARPHRD_EETHER); //Set HTYPE
    arpreq.arp_pro = htons(ETH_P_IP);      //Set PTYPE
    arpreq.arp_hln = ETHER_ADDR_LEN;       //Set HLEN
    arpreq.arp_pln = sizeof(in_addr_t);    //Set PLEN
    arpreq.arp_op = htons(ARPOP_REQUEST);  //Set Operation
    memset(&arpreq.arp_tha, 0, sizeof(arpreq.arp_tha));  //Set TargetHardwareAddress

    // insert target ip address into ARP request
    struct in_addr targetIpAddr = {0};
    if(!inet_aton(hostname.c_str(), &targetIpAddr)) {
      std::cerr << "Not an ip address!" << std::endl;
      // write to log
      return;
    }
    memcpy(&arpreq.arp_tpa, &targetIpAddr.s_addr, sizeof(arpreq.arp_tpa));  //Set TargetProtocolAddress

    // create network interface
    struct ifreq ifr;
    size_t ifNameLength = ifName.length();
    if(ifNameLength < sizeof(ifr.ifr_name)) {
      memcpy(ifr.ifr_name, ifName.c_str(), ifNameLength);
      ifr.ifr_name[ifNameLength] = 0;
    } else {
      std::cerr << "interface name to long!" << std::endl;
      // write to log
      return;
    }

    // Open IPv4 socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
      std::string err(strerror(errno));
      std::cerr << err << std::endl;
      //write to log
      return;
    }

    // Obtain source IP address. This has to be altered to perform ARP poisioning
    if(ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
      std::string err(strerror(errno));
      std::cerr << err << std::endl;
      // write to log
      close(fd);
      return;
    }
    // check if ifr is actually an ethernet interface
    /* if(ifr.ifr_hwaddr.sa_family != 1) { // because ARPHDR_ETHER = 1
      std::cerr << "not an ethernet interface!" << std::endl;
      // write to log
      close(fd);
      return;
    }
    */
    // inster source mac address into ethernet header and ARP request. Has to be altered for ARP poisioning
    const unsigned char* sourceMacAddr = (unsigned char*)ifr.ifr_hwaddr.sa_data;
    memcpy(header.ether_shost, sourceMacAddr, sizeof(header.ether_shost)); // sholdn't this be sizeof(sourceMacAddr) ?
    memcpy(&arpreq.arp_sha, sourceMacAddr, sizeof(arpreq.arp_sha));

    // Combine ethernet header and ARP request
    unsigned char frame[sizeof(struct ether_header) + sizeof(struct ether_arp)];
    memcpy(frame, &header, sizeof(struct ether_header));
    memcpy(frame + sizeof(struct ether_header), &arpreq, sizeof(struct ether_arp));

    // Open PCAP packet capture descriptor
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    pcap_errbuf[0] = '\0';
    pcap_t* pcap = pcap_open_live(ifName.c_str(), 96, 0, 0, pcap_errbuf);
    if(pcap_errbuf[0] != '\0') {
      // if something has been written to the errbuf
      std::cerr << pcap_errbuf << std::endl;
      // write to log
    }
    if(!pcap) {
      return;
    }

    // write ethernet frame to the network interface
    if(pcap_inject(pcap, frame, sizeof(frame)) == -1) {
      pcap_perror(pcap, 0);
      pcap_close(pcap);
      std::cerr << "pcap error!" << std::endl;
      // write to log
      return;
    }

    // close pcap descriptor
    pcap_close(pcap);
  }

}
