#include "Nuke.hpp"

void Nuke::fire(const std::string& ifName ) {
  std::string command = "./flood_router26 " + ifName;
  system(command.c_str());
}
