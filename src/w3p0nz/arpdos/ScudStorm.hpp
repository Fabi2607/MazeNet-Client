#ifndef SCUDSTORM_HPP
#define SCUDSTORM_HPP

#include <string>
#include <functional>

#include "ARPSpoofer.hpp"


/**
 * A simple interface to utter devastation. With only two simple methods you can run a DOS attack
 * against all enemy players with minimal network traffic. Isn't that great?
 */
class ScudStorm {

 public:
  using MessageHandler = std::function<bool(const u_char*)>;

  ScudStorm(std::string ifName);

  /**
   * Use this method to point your scud storm to the game server.
   * @targetIpAddr the ip address of the game server.
   */
  int lockTarget(uint32_t targetIpAddr);

  /**
   * This method fires the scud storm (launches the dos attack) and keeps the targets down
   * indefinitely (that means it won't return).
   */
  int fire(MessageHandler handler);

 private:

  bool locked;
  std::string interfaceName;
  ArpSpoofer spoofer;

  MessageHandler payload_handler_;


};

#endif
