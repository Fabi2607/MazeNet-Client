#ifndef ARPSCANNER_HPP
#define ARPSCANNER_HPP

#include <vector>
#include <string>

#include "ARPTarget.hpp"

class ArpScanner {

public:
  static std::vector<ArpTarget> arpScan(const std::string& ifName);

};

#endif
