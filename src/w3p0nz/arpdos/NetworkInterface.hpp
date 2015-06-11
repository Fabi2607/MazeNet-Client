#ifndef NETWORKINTERFACE_HPP
#define NETWORKINTERFACE_HPP

#include <boost/noncopyable.hpp>

#include <pcap.h>
#include "ARPPacket.hpp"

#include <string>
#include <vector>

class NetworkListener {
public:
  virtual void proccesPacket(ARPPacket packet) = 0;
  virtual ~NetworkListener();
};

class NetworkInterface : boost::noncopyable {

  std::string interfaceName;
  std::vector <NetworkListener> listeners;
  bool running;

  pcap_t* handle;

public:
  static NetworkInterface& instance();

  static void pcapProcessPacket(u_char* user, const struct pcap_pkthdr*, const u_char* packet);

  void init(std::string ifName);
  void stop();

  void registerListener(const NetworkListener& listener);
  void removeListener(const NetworkListener& listener);

private:
  NetworkInterface();
  void informListeners(ARPPacket packet);

};

#endif
