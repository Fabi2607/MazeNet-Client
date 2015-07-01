#ifndef NUKE_HPP
#define NUKE_HPP

#include <string>

/**
 * It's about time to fuck shit up! This refined weapon of mass destruction utilizes an EMP to
 * destroy(fuck up so badly that it needs to be rebooted) every technical device that isn't
 * sufficently protected(read: windows machine) in an area of one broadcast network. Use with caution!
 */
class Nuke {

public:
  /**
   * You dont have to target anything. This will just hit everything in your LAN.
   */
  void fire(const std::string& ifName);

};

#endif
